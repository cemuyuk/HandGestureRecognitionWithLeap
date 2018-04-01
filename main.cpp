//
//  main.cpp
//  LeapTesting2
//
//  Created by Cem Üyük on 20.03.2018.
//  Copyright © 2018 Cem Üyük. All rights reserved.
//


#include <iostream>
#include "Leap.h"

using namespace Leap;
bool exCode=true;

class SampleListener : public Listener {
public:
    virtual void onConnect(const Controller&);
    virtual void onFrame(const Controller&);
};

void SampleListener::onConnect(const Controller& controller) {
    std::cout << "Connected" << std::endl;
}

void SampleListener::onFrame(const Controller& controller) {
    const Frame frame = controller.frame();
    Leap::GestureList gestures = frame.gestures();
    
    Leap::Hand hand = frame.hands().frontmost();
    

         for(Leap::GestureList::const_iterator gl = gestures.begin();
             gl != frame.gestures().end(); gl++){
         
             if((*gl).type() == Leap::Gesture::TYPE_CIRCLE){
                         Leap::CircleGesture cGesture = Leap::Gesture::invalid();
                         cGesture = Leap::CircleGesture(*gl);
                         if(cGesture.radius()>90){
                             std::cout << "Circle." << std::endl;
                             exCode=false;
                         }
                 }
             if((*gl).type()==Leap::Gesture::TYPE_SWIPE){
                 Leap::SwipeGesture swipeGesture = Leap::Gesture::invalid();
                 swipeGesture = Leap::SwipeGesture(*gl);
                 Leap::Vector swipeDirection = swipeGesture.direction();
                 
                 if(swipeDirection.x < 0 && swipeGesture.position().x < -30){
                     std::cout << "Left direction" << std::endl;
                 }
                     if(swipeDirection.x > 0 && swipeGesture.position().x > 30){
                         std::cout << "Right direction" << std::endl;
                     }
                 }
                 if(!exCode)
                     break;
         }
}

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Circle to quit..." << std::endl;
    SampleListener listener;
    Controller controller;
    
    controller.enableGesture(Gesture::TYPE_CIRCLE);
    controller.enableGesture(Gesture::TYPE_KEY_TAP);
    controller.enableGesture(Gesture::TYPE_SCREEN_TAP);
    controller.enableGesture(Gesture::TYPE_SWIPE);
    controller.enableGesture(Gesture::TYPE_INVALID);
    
    controller.addListener(listener);
    
    while(exCode){
        if(!exCode){
            controller.removeListener(listener);
            return 0;
        }
    }
    return 0;
}
