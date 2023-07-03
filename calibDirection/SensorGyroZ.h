#include <Wire.h>

// turn 45 deg
const int32_t ang45 = 0x20000000;

// turn 90 deg
const int32_t ang90 = ang45 * 2;

// turn 1 deg
const int32_t ang1 = (ang45 + 22) / 45;

uint32_t ang = 0;
int16_t turnRate;
int16_t gyroOffset;
uint16_t temp = 0;

// reset ang value
void sensorReset(){
    temp = micros();
    ang = 0;
}

void sensorUpdate(){
    imu.readGyro(); // read gyro
    turnRate = imu.g.z - gyroOffset; // calculate angular vel

    uint16_t t = micros();
    uint16_t dt = t - temp; // calculate time elapsed
    temp = t; // update time stamp
  
    int32_t d_ang = (int32_t)turnRate * dt; //change in ang = ang vel * dt

    // (0.07 dps/digit) * (1/1000000 s/us) * (2^29/45 unit/degree)
    // = 14680064/17578125 unit/(digit*us)
    ang += (int64_t)d_ang*14680064/17578125;
}

void sensorSetup(){
    Wire.begin();
    imu.init();
    imu.enableDefault();
    imu.configureForTurnSensing();
    
    display.print(F("Gyro Calib"));
    delay(50);

    // calibration
    int32_t tot = 0;
    for(int i = 0; i< 1024; i++){
        while(!imu.gyroDataReady()){} // wait for new imu data
        imu.readGyro();
        tot += imu.g.z;
    }
    gyroOffset = tot/1024;
    sensorReset();
}
