# -*- coding: utf-8 -*-
"""
Created on Sat Apr  3 23:09:19 2021
@author: amine gasa
"""
import cv2
import os
import time
import handTrackingModule as htm
from computer import comp

wcam,hcam=640,480
cap=cv2.VideoCapture(0)
cap.set(3,wcam)
cap.set(4,hcam)
pTime=0
detector = htm.handDetector(detectionCon=0.75)
while True:
    success,img=cap.read()
    img = detector.findHands(img, draw=True )
    lmList=detector.findPosition(img,draw=False)
    #print(lmList)
    tipId=[4,8,12,16,20]
    if(len(lmList)!=0):
        fingers=[]
        #thumb
        if(lmList[tipId[0]][1]>lmList[tipId[0]-1][1]):
                fingers.append(1)
        else :
                fingers.append(0)
        #4 fingers
        for id in range(1,len(tipId)):
            
            if(lmList[tipId[id]][2]<lmList[tipId[id]-2][2]):
                fingers.append(1)
            
            else :
                fingers.append(0)
        
           
        cv2.rectangle(img,(20,255),(170,425),(0,255,0),cv2.FILLED)
        print(fingers.count(1))
        comp(fingers.count(1))
        
        cv2.putText(img,str(fingers.count(1)),(45,375),cv2.FONT_HERSHEY_PLAIN,
                                     10,(255,0,0),20)
        
     
    
    cTime=time.time()
    fps=1/(cTime-pTime)
    pTime=cTime
    cv2.putText(img, f'FPS: {int(fps)}',(400,70),cv2.FONT_HERSHEY_COMPLEX,1,(255,255,0),3)
    cv2.imshow("image",img)
    #time.sleep(0.001)
    
    if(cv2.waitKey(1) & 0xFF== ord('q')):
        break