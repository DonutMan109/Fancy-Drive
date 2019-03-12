#include "robot-config.h"
          

int main() {
    
clearScreen();    
    
while(1) {
if(Limit.pressing()){
    Brain.Screen.printAt(1, 20, "Pressing    ");
}
else {
    Brain.Screen.printAt(1, 20, "Not Pressing");
}
    
Variables();
Intakectrl();
Base();
Catapultctrl();
    
vex::task::sleep(20);
    } 
}
