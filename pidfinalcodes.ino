/*
   These are the possible conditions of the sensors
   0 1 1 1 1 1 1 1                          // error = -7
   0 0 1 1 1 1 1 1                          // error = -6
   0 0 0 1 1 1 1 1 || 1 0 1 1 1 1 1 1       // error = -5
   1 0 0 1 1 1 1 1                          // error = -4
   1 0 0 0 1 1 1 1 || 1 1 0 1 1 1 1 1       // error = -3
   1 1 0 0 1 1 1 1                          // error = -2
   1 1 0 0 0 1 1 1 || 1 1 1 0 1 1 1 1       // error = -1
   1 1 1 0 0 1 1 1                          // error = 0
   1 1 1 0 0 0 1 1 || 1 1 1 1 0 1 1 1       // error = 1
   1 1 1 1 0 0 1 1                          // error = 2
   1 1 1 1 0 0 0 1 || 1 1 1 1 1 0 1 1       // error = 3
   1 1 1 1 1 0 0 1                          // error = 4
   1 1 1 1 1 0 0 0 || 1 1 1 1 1 1 0 1       // error = 5
   1 1 1 1 1 1 0 0                          // error = 6
   1 1 1 1 1 1 1 0                          // error = 7

   Note : Adjust your connections and wiring in such a way that for "front(leftMotorSpeed , rightMotorSpeed)" the motor moves in forward direction.
   Also , make sure that pins 0 ans 1 of arduino are not connected to anything before uploading the code.

   If this program needs to be used on a white line with black background track then read the info given in the readSensors() function and change code accordingly


*/

#define s1  A0
#define s2  A1
#define s3  A2
#define s4  A3
#define s5  A4
#define s6  4
#define s7  3
#define s8  2
//#define LED A3

#define RIN1  6
#define RIN2  5
#define LIN1  7
#define LIN2  8

#define R_EN  9
#define L_EN  10

#define NO_OF_SENSORS   8
#define diff_const      17 //changed from 4-7-9-15-17
#define kd 65 //changed this from 23-35-55-65-90
#define baseMotorSpeed  90
//changed this from 70-95-110
#define turnspeed       90

uint8_t val[NO_OF_SENSORS] = {0, 0, 0, 0, 0, 0, 0, 0},prev_val[NO_OF_SENSORS]={0, 0, 0, 0, 0, 0, 0, 0}, sensors[NO_OF_SENSORS] = {s8, s7, s6, s5, s4, s3, s2, s1} , i = 0; int error_dir = 0; int difference = 0,last_difference = 0,stop = 0,PID_value=0,P=0,D=0;
int leftMotorSpeed = 0 , rightMotorSpeed = 0 ;
int flag ;
void front(int leftMotorSpeed , int rightMotorSpeed)
{
  digitalWrite(LIN1 , LOW);      // left motor front
  digitalWrite(LIN2 , HIGH);
  digitalWrite(RIN1 , HIGH);      // right motor front
  digitalWrite(RIN2 , LOW);

  analogWrite(L_EN , leftMotorSpeed);
 analogWrite(R_EN , rightMotorSpeed);
}

void reverse(int leftMotorSpeed , int rightMotorSpeed)
{
  digitalWrite(LIN1 , HIGH);       // left motor back
  digitalWrite(LIN2 , LOW);
  digitalWrite(RIN1 , LOW);       // right motor back
  digitalWrite(RIN2 , HIGH);

  analogWrite(L_EN , leftMotorSpeed);
  analogWrite(R_EN , rightMotorSpeed);
}

void rotate_CCW(int leftMotorSpeed , int rightMotorSpeed)
{
  digitalWrite(LIN1 , HIGH);      // left motor back
  digitalWrite(LIN2 , LOW);
  digitalWrite(RIN1 , HIGH);     // right motor front
  digitalWrite(RIN2 , LOW);

  analogWrite(L_EN , leftMotorSpeed);
 analogWrite(R_EN , rightMotorSpeed);
}

void rotate_CW(int leftMotorSpeed , int rightMotorSpeed)
{
  digitalWrite(LIN1 , LOW);      // left motor front
  digitalWrite(LIN2 , HIGH);
  digitalWrite(RIN1 , LOW);      // right motor back
  digitalWrite(RIN2 , HIGH);

  analogWrite(L_EN , leftMotorSpeed);
  analogWrite(R_EN , rightMotorSpeed);
}
void ruk() //stop motors
{
  digitalWrite(LIN1, LOW);
  digitalWrite(LIN2, LOW);
  digitalWrite(RIN1, LOW);
  digitalWrite(RIN2, LOW);
}
void prev()
{

  for(int i=0;i<NO_OF_SENSORS;i++)
  {
    prev_val[i]=val[i];
  }
}
void readSensors()
{
  //this function is to read the sensor values and store it in the "val" array
  Serial.println("INREAD");
  int j;
// delay(1000);
  for (i = 0, j = 0; i < 8 ; i++, j++)
  {
    val[j] = digitalRead(sensors[i]);//reading the values of the sensors
    Serial.print(val[j]);
    Serial.print(" ");
    // if used on white line with black background, uncomment the following statement(s) */
  }
  Serial.println();
   /*  if (val[0] ==0 && val[7] ==0 )
  {
     Serial.println("BLACK BACKGROUND");
//Serial.println("intial flag==0");
    flag=0;
    //pidblack();
    for ( j = 0; j < 8 ;  j++)
  {
     if(val[j]==0)
    {
        val[j]=1;
    }else if(val[j]==1)
    {
        val[j]=0;
    }
  }
  
  }
  else if (val[0] ==1 && val[7] ==1 )
  {
    flag=1;
    Serial.println("WHITE BACKGROUND");
    //pidwhite();   
  }
 else if (flag == 0 )
  {
     flag =0;
    Serial.println("BLACK BACKGROUND");
    // pidblack();
    for ( j = 0; j < 8 ;  j++)
  {
     if(val[j]==0)
    {
        val[j]=1;
    }else if(val[j]==1)
    {
        val[j]=0;
    }
  }
  }
   
  else if (flag == 1 )
  {
    flag=1;
   Serial.println("WHITE BACKGROUND");
  // pidwhite();
   
  }
    
    if(val[j]==0)
    {
        val[j]=1;
    }else if(val[j]==1)
    {
        val[j]=0;
    }
    //Serial.print(val[j]);
   */ 
  }

void detectLinePosition()
{
  //Serial.println("In line");
  if(val[0] ^ val[7])
    error_dir = val[0] - val[7];

  if(difference!=999 && difference!=-10 && difference!=10 && difference!=9 && difference!=last_difference)
  {
    last_difference = difference;
  }
  if (val[0] == 0 && val[1] == 1 && val[2] == 1 && val[3] == 1 && val[4] == 1 && val[5] == 1 && val[6] == 1 && val[7] == 1)

    difference = -7;
  //for a situation where there is left and straight line
  else if((val[0] == 0 && val[1] == 0 && val[2] == 0 && val[3] == 0 && val[4] == 1 && val[5] == 1 && val[6] == 1 && val[7] == 1) || (val[0] == 0 && val[1] == 0 && val[2] == 0 && val[3] == 0 && val[4] == 0 && val[5] == 1 && val[6] == 1 && val[7] == 1))
  {
      difference = -10;
  }
  //for a situation where there is right and straight line
  else if((val[0] == 1 && val[1] == 1 && val[2] == 1 && val[3] == 1 && val[4] == 0 && val[5] == 0 && val[6] == 0 && val[7] == 0) || (val[0] == 1 && val[1] == 1 && val[2] == 1 && val[3] == 0 && val[4] == 0 && val[5] == 0 && val[6] == 0 && val[7] == 0))
  {
    difference = 10;
    }
  else if (val[0] == 0 && val[1] == 0 && val[2] == 1 && val[3] == 1 && val[4] == 1 && val[5] == 1 && val[6] == 1 && val[7] == 1)

    difference = -6;

  else if (  (val[0] == 0 && val[1] == 0 && val[2] == 0 && val[3] == 1 && val[4] == 1 && val[5] == 1 && val[6] == 1 && val[7] == 1) || (val[0] == 1 && val[1] == 0 && val[2] == 1 && val[3] == 1 && val[4] == 1 && val[5] == 1 && val[6] == 1 && val[7] == 1) )

    difference = -5;

  else if (val[0] == 0 && val[1] == 0 && val[2] == 0 && val[3] == 0 && val[4] == 1 && val[5] == 1 && val[6] == 1 && val[7] == 1)

    difference = -5;

  else if (val[0] == 1 && val[1] == 0 && val[2] == 0 && val[3] == 1 && val[4] == 1 && val[5] == 1 && val[6] == 1 && val[7] == 1)

    difference = -4;

  else if (  (val[0] == 1 && val[1] == 0 && val[2] == 0 && val[3] == 0 && val[4] == 1 && val[5] == 1 && val[6] == 1 && val[7] == 1) || (val[0] == 1 && val[1] == 1 && val[2] == 0 && val[3] == 1 && val[4] == 1 && val[5] == 1 && val[6] == 1 && val[7] == 1) )

    difference = -3;


  else if (val[0] == 1 && val[1] == 1 && val[2] == 0 && val[3] == 0 && val[4] == 1 && val[5] == 1 && val[6] == 1 && val[7] == 1)

    difference = -2;

  else if (  (val[0] == 1 && val[1] == 1 && val[2] == 0 && val[3] == 0 && val[4] == 0 && val[5] == 1 && val[6] == 1 && val[7] == 1) )

    difference = -1;

  else if ((val[0] == 1 && val[1] == 1 && val[2] == 1 && val[3] == 0 && val[4] == 0 && val[5] == 1 && val[6] == 1 && val[7] == 1)||(val[0] == 1 && val[1] == 1 && val[2] == 1 && val[3] == 0 && val[4] == 1 && val[5] == 1 && val[6] == 1 && val[7] == 1)|| (val[0] == 1 && val[1] == 1 && val[2] == 1 && val[3] == 1 && val[4] == 0 && val[5] == 1 && val[6] == 1 && val[7] == 1))

    difference = 0;

  else if (  (val[0] == 1 && val[1] == 1 && val[2] == 1 && val[3] == 0 && val[4] == 0 && val[5] == 0 && val[6] == 1 && val[7] == 1)  )

    difference = 1;

  else if (val[0] == 1 && val[1] == 1 && val[2] == 1 && val[3] == 1 && val[4] == 0 && val[5] == 0 && val[6] == 1 && val[7] == 1)

    difference = 2;

  else if (  (val[0] == 1 && val[1] == 1 && val[2] == 1 && val[3] == 1 && val[4] == 0 && val[5] == 0 && val[6] == 0 && val[7] == 1) || (val[0] == 1 && val[1] == 1 && val[2] == 1 && val[3] == 1 && val[4] == 1 && val[5] == 0 && val[6] == 1 && val[7] == 1) )

    difference = 3;

  else if (val[0] == 1 && val[1] == 1 && val[2] == 1 && val[3] == 1 && val[4] == 1 && val[5] == 0 && val[6] == 0 && val[7] == 1)

    difference = 4;

  else if (  (val[0] == 1 && val[1] == 1 && val[2] == 1 && val[3] == 1 && val[4] == 1 && val[5] == 0 && val[6] == 0 && val[7] == 0) || (val[0] == 1 && val[1] == 1 && val[2] == 1 && val[3] == 1 && val[4] == 1 && val[5] == 1 && val[6] == 0 && val[7] == 1) )

    difference = 5;

  else if (val[0] == 1 && val[1] == 1 && val[2] == 1 && val[3] == 1 && val[4] == 1 && val[5] == 1 && val[6] == 0 && val[7] == 0)

    difference = 6;

  else if (val[0] == 1 && val[1] == 1 && val[2] == 1 && val[3] == 1 && val[4] == 1 && val[5] == 1 && val[6] == 1 && val[7] == 0)

    difference = 7;
  
  else if (val[0] == 1 && val[1] == 1 && val[2] == 1 && val[3] == 1 && val[4] == 1 && val[5] == 1 && val[6] == 1 && val[7] == 1)
  {
    // when the bot goes out of the line
    readSensors();
    if((val[0] == 1 && val[1] == 1 && val[2] == 1 && val[3] == 1 && val[4] == 1 && val[5] == 1 && val[6] == 1 && val[7] == 1) && ((prev_val[0] == 1 && prev_val[1] == 1 && prev_val[2] == 0 && prev_val[3] == 0 && prev_val[4] == 0 && prev_val[5] == 1 && prev_val[6] == 1 && prev_val[7] == 1) || (prev_val[0] == 1 && prev_val[1] == 1 && prev_val[2] == 1 && prev_val[3] == 0 && prev_val[4] == 0 && prev_val[5] == 0 && prev_val[6] == 1 && prev_val[7] == 1) || (prev_val[0] == 1 && prev_val[1] == 1 && prev_val[2] == 0 && prev_val[3] == 0 && prev_val[4] == 1 && prev_val[5] == 1 && prev_val[6] == 1 && prev_val[7] == 1) || (prev_val[0] == 1 && prev_val[1] == 1 && prev_val[2] == 1 && prev_val[3] == 0 && prev_val[4] == 0 && prev_val[5] == 1 && prev_val[6] == 1 && prev_val[7] == 1)))
    {
      difference = 0;
    }
    if(val[0] == 1 && val[1] == 1 && val[2] == 1 && val[3] == 1 && val[4] == 1 && val[5] == 1 && val[6] == 1 && val[7] == 1)
    {
      if (error_dir < 0)
      {
        difference = -9;
      }
      else if (error_dir > 0)
      {
        difference = 9;
      }
      else
      {
        difference = 0;
      }
    }else
    {
      difference=0;
    }

  }
  if ((val[0] == 0 && val[1] == 0 && val[2] == 0 && val[3] == 0 && val[4] == 0 && val[5] == 0 && val[6] == 0 && val[7] == 0)||(val[0] == 0 && val[1] == 0 && val[2] == 0 && val[3] == 0 && val[4] == 0 && val[5] == 0 && val[6] == 0 && val[7] == 1)|| (val[0] == 1 && val[1] == 0 && val[2] == 0 && val[3] == 0 && val[4] == 0 && val[5] == 0 && val[6] == 0 && val[7] == 0)||(val[0] == 1 && val[1] == 0 && val[2] == 0 && val[3] == 0 && val[4] == 0 && val[5] == 0 && val[6] == 0 && val[7] == 1)|| (val[0] == 0 && val[1] == 0 && val[2] == 0 && val[3] == 0 && val[4] == 0 && val[5] == 0 && val[6] == 1 && val[7] == 1)||(val[0] == 1 && val[1] == 1 && val[2] == 0 && val[3] == 0 && val[4] == 0 && val[5] == 0 && val[6] == 0 && val[7] == 0)||(val[0] == 1 && val[1] == 1 && val[2] == 1 && val[3] == 0 && val[4] == 0 && val[5] == 0 && val[6] == 0 && val[7] == 0) || (val[0] == 0 && val[1] == 0 && val[2] == 0 && val[3] == 0 && val[4] == 0 && val[5] == 1 && val[6] == 1 && val[7] == 1) )
  {
    // when the bot reaches a checkpoint / a stop
    prev(); //to store previous sensor values in a copy array
    delay(50); //time to gauge whether it was a stop or checkpoint
    readSensors();
    /** Below if statement is for detection of stop on a black line
    *  if wanna detect white stop line
    * use the commented if condition
    **/
    if((val[0]==prev_val[0] && val[1]==prev_val[1] && val[2]==prev_val[2] && val[3]==prev_val[3] && val[4]==prev_val[4] && val[5]==prev_val[5] && val[6]==prev_val[6] && val[7]==prev_val[7]) && (val[0]==0 && val[1]==0 && val[2]==0 && val[3]==0 && val[4]==0 && val[5]==0 && val[6]==0 && val[7]==0))
    {

        ruk();
        difference=999;
//        digitalWrite(LED,HIGH);
        delay(500);
//        digitalWrite(LED,LOW);
    }
    /*
    if((val[0]==prev_val[0] && val[1]==prev_val[1] && val[2]==prev_val[2] && val[3]==prev_val[3] && val[4]==prev_val[4] && val[5]==prev_val[5] && val[6]==prev_val[6] && val[7]==prev_val[7]) && (val[0]==1 && val[1]==1 && val[2]==1 && val[3]==1 && val[4]==1 && val[5]==1 && val[6]==1 && val[7]==1))
    {

        ruk();
        difference=999;
        digitalWrite(LED,HIGH);
        delay(500);
        digitalWrite(LED,LOW);
    }
    */
    /*else if((val[0] == 0 && val[1] == 0 && val[2] == 0 && val[3] == 0 && val[4] == 0 && val[5] == 0 && val[6] == 0 && val[7] == 0)||(val[0] == 0 && val[1] == 0 && val[2] == 0 && val[3] == 0 && val[4] == 0 && val[5] == 0 && val[6] == 0 && val[7] == 1)|| (val[0] == 1 && val[1] == 0 && val[2] == 0 && val[3] == 0 && val[4] == 0 && val[5] == 0 && val[6] == 0 && val[7] == 0)||(val[0] == 1 && val[1] == 0 && val[2] == 0 && val[3] == 0 && val[4] == 0 && val[5] == 0 && val[6] == 0 && val[7] == 1)|| (val[0] == 0 && val[1] == 0 && val[2] == 0 && val[3] == 0 && val[4] == 0 && val[5] == 0 && val[6] == 1 && val[7] == 1)||(val[0] == 1 && val[1] == 1 && val[2] == 0 && val[3] == 0 && val[4] == 0 && val[5] == 0 && val[6] == 0 && val[7] == 0)||(val[0] == 1 && val[1] == 1 && val[2] == 1 && val[3] == 0 && val[4] == 0 && val[5] == 0 && val[6] == 0 && val[7] == 0) || (val[0] == 0 && val[1] == 0 && val[2] == 0 && val[3] == 0 && val[4] == 0 && val[5] == 1 && val[6] == 1 && val[7] == 1))*/
    else
    {
//      digitalWrite(LED,HIGH);
      delay(20);
//      digitalWrite(LED,LOW);
      difference = 0;
  }
/*}else
    {
      difference = 0;
  }*/
//    digitalWrite(LED,LOW);

}
}

void controlMotors()
{
  Serial.print("Difference = ");
  Serial.println(difference);
    if (difference == -9)
    {
      while ((val[0] == 1 && val[1] == 1 && val[2] == 1 && val[3] == 1 && val[4] == 1 && val[5] == 1 && val[6] == 1 && val[7] == 1))
      {
        rotate_CCW(turnspeed , turnspeed);
        readSensors();
        detectLinePosition();
        if (!(val[0] == 1 && val[1] == 1 && val[2] == 1 && val[3] == 1 && val[4] == 1 && val[5] == 1 && val[6] == 1 && val[7] == 1) && difference>-9)
        {
          //ruk();
          break;
        }
      }
      error_dir = 0;
    }
    else if (difference == 9)
    {
      while ((val[0] == 1 && val[1] == 1 && val[2] == 1 && val[3] == 1 && val[4] == 1 && val[5] == 1 && val[6] == 1 && val[7] == 1))
      {
        rotate_CW(turnspeed,turnspeed);
        readSensors();
        detectLinePosition();
        if (!(val[0] == 1 && val[1] == 1 && val[2] == 1 && val[3] == 1 && val[4] == 1 && val[5] == 1 && val[6] == 1 && val[7] == 1) && difference<9)
        {
          //ruk();
          break;
        }
      }
      error_dir = 0;
    }
    /*else if (difference == 999)
    {
      ruk();
    }*/
    else if(difference == -10)
    {
      while((val[0] == 0 && val[1] == 0 && val[2] == 0 && val[3] == 0 && val[4] == 1 && val[5] == 1 && val[6] == 1 && val[7] == 1) || (val[0] == 0 && val[1] == 0 && val[2] == 0 && val[3] == 0 && val[4] == 0 && val[5] == 1 && val[6] == 1 && val[7] == 1))
      {
        rotate_CCW(turnspeed,turnspeed);
        readSensors();
        if(!((val[0] == 0 && val[1] == 0 && val[2] == 0 && val[3] == 0 && val[4] == 1 && val[5] == 1 && val[6] == 1 && val[7] == 1) || (val[0] == 0 && val[1] == 0 && val[2] == 0 && val[3] == 0 && val[4] == 0 && val[5] == 1 && val[6] == 1 && val[7] == 1)))
        {
          //ruk();
          break;
        }
      }
    }
    else if(difference == 10)
    {
      while((val[0] == 1 && val[1] == 1 && val[2] == 1 && val[3] == 1 && val[4] == 0 && val[5] == 0 && val[6] == 0 && val[7] == 0) || (val[0] == 1 && val[1] == 1 && val[2] == 1 && val[3] == 0 && val[4] == 0 && val[5] == 0 && val[6] == 0 && val[7] == 0))
      {
        rotate_CW(turnspeed,turnspeed);
        readSensors();
        if(!((val[0] == 1 && val[1] == 1 && val[2] == 1 && val[3] == 1 && val[4] == 0 && val[5] == 0 && val[6] == 0 && val[7] == 0) || (val[0] == 1 && val[1] == 1 && val[2] == 1 && val[3] == 0 && val[4] == 0 && val[5] == 0 && val[6] == 0 && val[7] == 0)))
        {
          //ruk();
          delay(10);
          break;
        }
      }
    }
    else if(difference==999)
    {

    }
    else
    {
      P=difference*diff_const;
      D=(difference-last_difference)*kd;
      PID_value=P+D;
      leftMotorSpeed = baseMotorSpeed + PID_value;
      rightMotorSpeed = baseMotorSpeed - PID_value;
      leftMotorSpeed = (leftMotorSpeed < 0) ? 0 : leftMotorSpeed;
      rightMotorSpeed = (rightMotorSpeed < 0) ? 0 : rightMotorSpeed;
      leftMotorSpeed = constrain(leftMotorSpeed , 0 , 150);
      rightMotorSpeed = constrain(rightMotorSpeed , 0 , 150);
      //Serial.print("Left motor = ");
      //Serial.println(leftMotorSpeed);
      //Serial.print("Right motor = ");
      //Serial.println(rightMotorSpeed);
      front(leftMotorSpeed , rightMotorSpeed);
      if(D!=0)
        delay(15);
      //delay(5000);
    }

}

void setup()
{

  Serial.begin(9600);
  for (i = 0 ; i < NO_OF_SENSORS ; i++)
    pinMode(sensors[i], INPUT);
  
  pinMode(RIN1 , OUTPUT);
  pinMode(RIN2 , OUTPUT);
  pinMode(LIN1 , OUTPUT);
  pinMode(LIN2 , OUTPUT);
  pinMode(rightMotorSpeed , OUTPUT);
  pinMode(leftMotorSpeed , OUTPUT);
//  pinMode(LED,OUTPUT);
  pinMode(A5,OUTPUT);
  digitalWrite(A5,LOW);
}

void loop()
{
  //Serial.println("HI");
  readSensors();
  detectLinePosition();
  controlMotors();
  //delay(3000);
}
