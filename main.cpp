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
bool exCode=false;

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
                             exCode=true;
                         }
             }else if((*gl).type()==Leap::Gesture::TYPE_SWIPE){
                 Leap::SwipeGesture swipeGesture = Leap::Gesture::invalid();
                 swipeGesture = Leap::SwipeGesture(*gl);
                 Leap::Vector swipeDirection = swipeGesture.direction();
                 
                 if(swipeGesture.pointable().hand().palmNormal().x < 0 || swipeGesture.pointable().hand().palmNormal().x > 0 ){
                     if(swipeDirection.x < 0 && swipeGesture.position().x < -40){
                     std::cout << "Left direction" << std::endl;
                     }
                     if(swipeDirection.x > 0 && swipeGesture.position().x > 40){
                         std::cout << "Right direction" << std::endl;
                     }
                 }
                 
              
                 
             }else{
                 Leap::Pointable ptbl = (*gl).pointables().frontmost();
                 
                 if(ptbl.ZONE_TOUCHING){
                     std::cout << "Key Tap buddy." << std::endl;
                 }else{
                     std::cout << "Screen Tap buddy." << std::endl;
                 }
             }
             
             /*
             else  if((*gl).type()==Leap::Gesture::TYPE_SCREEN_TAP){
                
                 
                Leap::ScreenTapGesture scrTapGest = Leap::Gesture::invalid();
                scrTapGest = Leap::ScreenTapGesture(*gl);
                 
                Leap::Pointable scrTapPointable = scrTapGest.pointable();
                
                if(scrTapPointable.hand().palmNormal().y < 0 &&
                   scrTapPointable.ZONE_HOVERING){
                        std::cout << "Screen Tap buddy." << std::endl;
                }
                 
             }else if((*gl).type()==Leap::Gesture::TYPE_KEY_TAP){
                 
                Leap::KeyTapGesture keyTapGest = Leap::Gesture::invalid();
                keyTapGest = Leap::KeyTapGesture(*gl);
                 
                Leap::Pointable keyTapPointable = keyTapGest.pointable();
                
                 if(keyTapPointable.hand().palmNormal().y < 0
                    && keyTapPointable.ZONE_TOUCHING){
                        std::cout << "Key Tap buddy." << std::endl;
                    
                }
             }
             */
             if(exCode) break;
         }
}

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Circle to quit..." << std::endl;
    SampleListener listener;
    Controller controller;
    
    /*
    controller.config().setFloat("Gesture.KeyTap.MinDownVelocity", 30.0);
    controller.config().setFloat("Gesture.KeyTap.HistorySeconds", .2);
    controller.config().setFloat("Gesture.KeyTap.MinDistance", 6.0);
    controller.config().save();
    
    controller.config().setFloat("Gesture.ScreenTap.MinDownVelocity", 30.0);
    controller.config().setFloat("Gesture.ScreenTap.HistorySeconds", .2);
    controller.config().setFloat("Gesture.ScreenTap.MinDistance", 6.0);
    controller.config().save();
     */
    
    controller.enableGesture(Gesture::TYPE_CIRCLE);
    controller.enableGesture(Gesture::TYPE_SWIPE);
    controller.enableGesture(Gesture::TYPE_SCREEN_TAP);
    controller.enableGesture(Gesture::TYPE_KEY_TAP);
    controller.enableGesture(Gesture::TYPE_INVALID);
    
    controller.addListener(listener);
    
    while(!exCode){
        if(exCode){
            controller.removeListener(listener);
            return 0;
        }
    }
    return 0;
}
