import cvzone
import cv2

cap = cv2.VideoCapture(0)
if not cap.isOpened():
    print("Error: Camera could not be opened.")
    exit()

detector = cvzone.HandDetector(maxHands=5,detectionCon=1)
while True:
    success, img = cap.read()
    img = detector.findHands(img)
    lmList, bbox = detector.findPosition(img)
    if lmList:
        fingers = detector.fingersUp()
        print(fingers)
    cv2.imshow("Image", img)
    cv2.waitKey(1)