#include "mbed.h"
#include <array>

#define TARGET_TX_PIN USBTX
#define TARGET_RX_PIN USBRX
#define MAXIMUM_BUFFER_SIZE 0
#define BY_FW_POWER 20000
#define BY_BW_POWER 20000
#define POWER 25000
#define TEISOKUPOWER 7000

// キーたち
#define UP_KEY 'u'
#define DOWN_KEY 'o'

#define FW_KEY '8'
#define BW_KEY '5'
#define FR_KEY '9'
#define BR_KEY '6'
#define FL_KEY '7'
#define BL_KEY '4'
#define LTRR_KEY '3'
#define LTRL_KEY '2'

#define BY_FW_KEY '1'
#define BY_BW_KEY '0'
#define SL_ARM_KEY '.'
#define SL_ON_KEY '+'

#define SERB_KEY '6'
#define SERW_KEY '9'
#define SER180_KEY '1'
#define SER0_KEY '3'
#define SER90_KEY '2'
#define SER45_KEY '4'
#define SER135_KEY '5'

#define TEISOKU_KEY '*'

DigitalIn button{BUTTON1};
DigitalOut led{LED1};

BufferedSerial serial_port(USBTX, USBRX);
BufferedSerial uart4(PA_9, PA_10);

bool FW = false;
bool BW = false;
bool FR = false;
bool BR = false;
bool BL = false;
bool FL = false;
bool BY_FW = false;
bool BY_BW = false;

bool SL_ARM = false;
bool SL_ON = false;
bool SWICH = false;
bool SERtheta = false;

bool SERW = false;
bool SER180 = false;
bool SER0 = false;
bool SER90 = false;
bool SERB = false;
bool SER45 = false;
bool SER135 = false;
bool LTRR = false;
bool LTRL = false;

bool TEISOKU = false;

char buf[1] = {0};

bool limit = 0;

int theta = 0;

void SERhan(char ny)
{
   if (ny == SERB_KEY)
   {
      SERB = true;
      SER180 = false;
      SER0 = false;
      SER90 = false;
      SERW = false;
      SERtheta = false;
      SER45 = false;
      SER135 = false;
   }
   else if (ny == SERW_KEY)
   {
      SERB = false;
      SER180 = false;
      SER0 = false;
      SER90 = false;
      SERW = true;
      SERtheta = false;
      SER45 = false;
      SER135 = false;
   }
   else if (ny == SER0_KEY)
   {
      SERB = false;
      SER180 = false;
      SER0 = true;
      SER90 = false;
      SERW = false;
      SERtheta = false;
      SER45 = false;
      SER135 = false;
   }
   else if (ny == SER90_KEY)
   {
      SERB = false;
      SER180 = false;
      SER0 = false;
      SER90 = true;
      SERW = false;
      SERtheta = false;
      SER45 = true;
      SER135 = false;
   }
   else if (ny == SER180_KEY)
   {
      SERB = false;
      SER180 = true;
      SER0 = false;
      SER90 = false;
      SERW = false;
      SERtheta = false;
      SER45 = true;
      SER135 = false;
   }
   if (ny == SER45_KEY)
   {
      SERB = false;
      SER180 = false;
      SER0 = false;
      SER90 = false;
      SERW = false;
      SERtheta = false;
      SER45 = true;
      SER135 = false;
   }
   if (ny == SER135_KEY)
   {
      SERB = false;
      SER180 = false;
      SER0 = false;
      SER90 = false;
      SERW = false;
      SERtheta = false;
      SER45 = false;
      SER135 = true;
   }
}

void hantei(char ny)
{
   if (ny == LTRR_KEY)
   {
      LTRR = true;
      LTRL = false;
      FW = false;
      BW = false;
      FR = false;
      FL = false;
      BR = false;
      BL = false;
      BY_FW = false;
      BY_BW = false;
   }
   if (ny == LTRL_KEY)
   {
      LTRR = false;
      LTRL = true;
      FW = false;
      BW = false;
      FR = false;
      FL = false;
      BR = false;
      BL = false;
      BY_FW = false;
      BY_BW = false;
   }
   if (ny == FW_KEY)
   {
      LTRL = false;
      LTRR = false;
      FW = true;
      BW = false;
      FR = false;
      FL = false;
      BR = false;
      BL = false;
      BY_FW = false;
      BY_BW = false;
   }
   if (ny == BW_KEY)
   {
      LTRL = false;
      LTRR = false;
      FW = false;
      BW = true;
      FR = false;
      FL = false;
      BR = false;
      BL = false;
      BY_FW = false;
      BY_BW = false;
   }
   if (ny == FR_KEY)
   {
      LTRL = false;
      LTRR = false;
      FW = false;
      BW = false;
      FR = true;
      FL = false;
      BR = false;
      BL = false;
      BY_FW = false;
      BY_BW = false;
   }
   if (ny == FL_KEY)
   {
      LTRL = false;
      LTRR = false;
      FW = false;
      BW = false;
      FR = false;
      FL = true;
      BR = false;
      BL = false;
      BY_FW = false;
      BY_BW = false;
   }
   if (ny == BR_KEY)
   {
      LTRL = false;
      LTRR = false;
      FW = false;
      BW = false;
      FR = false;
      FL = false;
      BR = true;
      BL = false;
      BY_FW = false;
      BY_BW = false;
   }
   if (ny == BL_KEY)
   {
      LTRL = false;
      LTRR = false;
      FW = false;
      BW = false;
      FR = false;
      FL = false;
      BR = false;
      BL = true;
      BY_FW = false;
      BY_BW = false;
   }
   if (ny == BY_FW_KEY)
   {
      LTRL = false;
      LTRR = false;
      FW = false;
      BW = false;
      FR = false;
      FL = false;
      BR = false;
      BL = false;
      BY_FW = true;
      BY_BW = false;
   }
   if (ny == BY_BW_KEY)
   {
      LTRL = false;
      LTRR = false;
      FW = false;
      BW = false;
      FR = false;
      FL = false;
      BR = false;
      BL = false;
      BY_FW = false;
      BY_BW = true;
   }
   if (ny == SL_ARM_KEY)
   {
      if (SL_ARM)
      {
         SL_ARM = false;
      }
      else
      {
         SL_ARM = true;
      }
   }
   if (ny == SL_ON_KEY)
   {
      if (SL_ON)
      {
         SL_ON = false;
      }
      else
      {
         SL_ON = true;
      }
   }
   if (ny == TEISOKU_KEY)
   {
      if (TEISOKU)
      {
         TEISOKU = false;
      }
      else
      {
         TEISOKU = true;
      }
   }
}

// DigitalIn limit1(PB_4);
// DigitalIn limit2(PB_5);
// DigitalIn limit3(PB_3);
// DigitalIn limit4(PB_10);

int main()
{

   CAN can(PA_11, PA_12, (int)1e6);
   CANMessage msg;
   CANMessage SER_msg;
   CANMessage servo_msg;

   uart4.set_baud(9600);
   serial_port.set_baud(115200);

   printf("setup\n");

   while (1)
   {

      int16_t pwm[4] = {0, 0, 0, 0};
      std::array<uint8_t, 8> SER = {0, 0, 0, 0, 0, 0, 0, 0};
      std::array<uint8_t, 8> servo;
      std::fill(servo.begin(), servo.end(), 0);

      if (uart4.readable())
      {
         led = !led;
         uart4.read(buf, sizeof(buf));

         char ny = buf[0];
         printf("%d", ny);

         if (ny == 'd')
         {
            SWICH = true;
         }
         else if (ny == 'u')
         {
            SWICH = false;
            FW = false;
            BW = false;
            FR = false;
            FL = false;
            BR = false;
            BL = false;
            BY_FW = false;
            BY_BW = false;
            SERB = false;
            SERW = false;
         }
         if (ny == '.')
         {
            SERtheta = true;
         }
         if (SERtheta && SWICH)
         {
            SERhan(ny);
         }
         else if (SWICH)
         {
            hantei(ny);
         }
      }
      if (TEISOKU == false)
      {
         if (FW)
         {
            pwm[1] = -POWER;
            pwm[2] = POWER;
         }
         else if (BW)
         {
            pwm[1] = POWER;
            pwm[2] = -POWER;
         }
         else if (FR)
         {
            pwm[2] = POWER;
         }
         else if (FL)
         {
            pwm[1] = -POWER;
         }
         else if (BR)
         {
            pwm[2] = -POWER;
         }
         else if (BL)
         {
            pwm[1] = POWER;
         }
         else if (LTRR)
         {
            pwm[1] = -POWER;
            pwm[2] = -POWER;
         }
         else if (LTRL)
         {
            pwm[1] = POWER;
            pwm[2] = POWER;
         }
      }
      else if (TEISOKU)
      {
         pwm[0] = 10000;
         if (FW)
         {
            pwm[1] = -TEISOKUPOWER;
            pwm[2] = TEISOKUPOWER;
         }
         else if (BW)
         {
            pwm[1] = TEISOKUPOWER;
            pwm[2] = -TEISOKUPOWER;
         }
         else if (FR)
         {
            pwm[2] = TEISOKUPOWER;
         }
         else if (FL)
         {
            pwm[1] = -TEISOKUPOWER;
         }
         else if (BR)
         {
            pwm[2] = -TEISOKUPOWER;
         }
         else if (BL)
         {
            pwm[1] = TEISOKUPOWER;
         }
      }
      if (BY_FW)
      {
         pwm[3] = -BY_FW_POWER;
      }
      else if (BY_BW)
      {
         pwm[3] = BY_BW_POWER;
      }
      if (SERB)
      {
         theta += 1;
         ThisThread::sleep_for(30ms);
         printf("A");
      }
      if (SERW)
      {
         theta += -1;
         ThisThread::sleep_for(30ms);
         printf("a");
      }
      if (SER0)
         theta = 0;
      if (SER45)
         theta = 63;
      if (SER90)
         theta = 127;
      if (SER135)
         theta = 190;
      if (SER180)
         theta = 235;

      if (SL_ON)
      {
         std::fill(SER.begin(), SER.end(), 255);
      }
      // std::array<uint8_t, 8> sin_SER;
      // std::array<uint8_t, 1> sec_SER;
      // for (int i = 0; i < 8; i++)
      // {
      //    sin_SER[i] = (SER[i] << i);
      // }

      // for (int i = 0; i < 8; i++)
      // {
      //    sec_SER[0] += sin_SER[i];
      //

      CANMessage msg(2, (const uint8_t *)pwm, 8);
      can.write(msg);
      CANMessage SER_msg(28, SER.data(), 8);
      can.write(SER_msg);
      if (theta < 0)
      {
         theta = 0;
      }
      else if (theta > 235)
      {
         theta = 235;
      }
      std::fill(servo.begin(), servo.end(), theta);
      CANMessage servo_msg(141, servo.data(), 8);
      can.write(servo_msg);
   }
}