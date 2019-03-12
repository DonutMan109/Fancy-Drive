//Perifs
vex::brain Brain;
vex::controller Controller1 = vex::controller();
vex::motor Left1 = vex::motor(vex::PORT1,false);
vex::motor Left2 = vex::motor(vex::PORT2,true);
vex::motor Left3 = vex::motor(vex::PORT4,false);
vex::motor Right1 = vex::motor(vex::PORT11,false);
vex::motor Right2 = vex::motor(vex::PORT6,true);
vex::motor Right3 = vex::motor(vex::PORT7,true);
vex::motor Intake = vex::motor(vex::PORT17, false);
vex::motor Catapult = vex::motor(vex::PORT9, false);
vex::limit Limit = vex::limit(Brain.ThreeWirePort.H);

//Variables
int RightJoyMV; //Main Right Y
int LeftJoyMV;  //Main Left Y
int LeftJoyMH; //Main Left X
int RightJoyMH; //Main Right X


//Functions
void Intakectrl(){
    if(Controller1.ButtonR2.pressing()) {
        Intake.spin(vex::directionType::rev, 100, vex::velocityUnits::pct);
    }
    else if(Controller1.ButtonR1.pressing()) {
        Intake.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
    }
    else {
        Intake.stop();
    }
}

void Variables(){
    RightJoyMV = Controller1.Axis2.value(); //Main Right Y
    LeftJoyMV = Controller1.Axis3.value();  //Main Left Y
    LeftJoyMH = Controller1.Axis4.value(); //Main Left X
    RightJoyMH = Controller1.Axis1.value(); //Main Right X
}

void clearScreen(){
    Brain.Screen.clearScreen(vex::color::blue);
}

void Cata(int pwr){
    Catapult.spin(vex::directionType::fwd, pwr, vex::velocityUnits::pct);
}

void Catacoast(){
    Catapult.stop(vex::brakeType::coast);
}

void Catahold(){
    Catapult.stop(vex::brakeType::hold);
}

void lDrive(int pwr){//intake power
    Left1.spin(vex::directionType::fwd, pwr, vex::velocityUnits::pct);
    Left2.spin(vex::directionType::fwd, pwr, vex::velocityUnits::pct);
    Left3.spin(vex::directionType::fwd, pwr, vex::velocityUnits::pct);
    
	//motor[mLeftMiddle] = PowerCap(pwr);
	//motor[mLeftFront] = PowerCap(pwr);
	//motor[mLeftBack] = PowerCap(pwr);
	//Set left motors to a certain power
}

void rDrive(int pwr){//intake power
    Right1.spin(vex::directionType::fwd, pwr, vex::velocityUnits::pct);
    Right2.spin(vex::directionType::fwd, pwr, vex::velocityUnits::pct);
    Right3.spin(vex::directionType::fwd, pwr, vex::velocityUnits::pct);
    
	//motor[mRightMiddle] = PowerCap(pwr);
	//motor[mRightFront] = PowerCap(pwr);
	//motor[mRightBack] = PowerCap(pwr);
	//Set right motors to a certain power
}

void Base(){//Configure base control joysticks
	if((LeftJoyMV != 0 && RightJoyMV != 0)){
		rDrive(RightJoyMV);
		lDrive(LeftJoyMV);
    
		} else {
		rDrive(LeftJoyMV + RightJoyMV - (LeftJoyMH + RightJoyMH));
		lDrive(LeftJoyMV + RightJoyMV + (LeftJoyMH + RightJoyMH));
	}
}

void Catapultctrl(){
    if(Controller1.ButtonL1.pressing()) {
        //Catacoast();
        Cata(100);
        vex::task::sleep(1000);
        while(!Limit.pressing()){
            Cata(100);
            Variables();
            Intakectrl();
            Base();
        }
        Catacoast();
    }
}
