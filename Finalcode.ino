


float kp = 150;
float ki = 0.5;
float kd = 0.5;



int maxSpeed = 255;
int error = 0;
int p , i , d , ePrime = 0;

int LSensor = 2;
int RSensor = 4;
int Lmotor1 = 7;
int Lmotor2 = 8;
int Rmotor1 = 5;
int Rmotor2 = 6;
int ENA = 10;
int ENB = 11;


void setup(){
  Serial.begin(9600);
  pinMode(Lmotor1 , OUTPUT);
  pinMode(Rmotor1 , OUTPUT);
  pinMode(Lmotor2 , OUTPUT);
  pinMode(Rmotor2 , OUTPUT);
  pinMode(ENA , OUTPUT);
  pinMode(ENB , OUTPUT); 
  pinMode(LSensor ,INPUT);
  pinMode(RSensor ,INPUT);
  
}

void PID(){
  
    p = error;
    i = i + error;
    d = d - ePrime;
    ePrime = error;
    int pidValue = p * kp + ki * i + kd * d;
    int baseSpeed = 220;
    int leftmotorSpeed = baseSpeed + pidValue; // assumption : e > 0 => trun right
    int rightmotorSpeed = baseSpeed - pidValue;
  
    // speed limitation
    if (leftmotorSpeed > maxSpeed){
      leftmotorSpeed = maxSpeed;
    }
    
    if (rightmotorSpeed > maxSpeed){
      rightmotorSpeed = maxSpeed;
    }
  
    if (leftmotorSpeed < 0){
      leftmotorSpeed = 0;
    }
  
    if (rightmotorSpeed < 0){
      rightmotorSpeed = 0;
    }
  analogWrite(ENA , leftmotorSpeed);
  analogWrite(ENB , rightmotorSpeed);
  
  Serial.print(leftmotorSpeed);
  Serial.print(" ");

  Serial.println(rightmotorSpeed);
 

  //Serial.println(pidValue);
  

  //Serial.println(p);
  

  //Serial.println(i);
  

  //Serial.println(d);
 
  
}

void loop(){
  forward();
  PID();
  


  
  if (digitalRead(2) == 1 and digitalRead(4) == 0){
    error = -1;
    
  }
  
  else if (digitalRead(2) == 0 and digitalRead(4) == 0){
    error = 0;
    
  }

  else if (digitalRead(2) == 0 and digitalRead(4) == 1){ 
    error = 1;
    
  }
}

void forward(){
  digitalWrite(Lmotor1 , HIGH);
  digitalWrite(Lmotor2 , LOW);
  digitalWrite(Rmotor1 , LOW);
  digitalWrite(Rmotor2 , HIGH);
}
