# -*- coding: utf-8 -*-
import cv2


def Optimize(aSrcMat, aBlockSize=15, aConstant=10.00):
    if len(aSrcMat.shape) > 2:  # Single channel이 아니면
        aSrcMat = cv2.cvtColor(aSrcMat, cv2.COLOR_BGR2GRAY)
    sDstMat = cv2.adaptiveThreshold(aSrcMat, \
                                    255, \
                                    cv2.ADAPTIVE_THRESH_MEAN_C, \
                                    cv2.THRESH_BINARY, \
                                    aBlockSize, \
                                    aConstant)
    return sDstMat


## Test Section
if __name__ == '__main__':
    # Test adaptiveThreshold
    img = cv2.imread('Images/test.png')

    out = Optimize(img)

    cv2.imshow("Thr", out)
    cv2.waitKey(0)
