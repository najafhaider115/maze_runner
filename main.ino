///#######################
//Program for checking auto correction

///#######################
/* Thing to notice 
See there will be three time. 
time1 == time taken to turn left or right.
time2 == time taken to turn 180.
time3 == time taken to turn slight left or slight right.
*/
int const time1=100;
int const time2=3000;
int const time3=6000;
// four digital pins for motor driver
int md1=2;
int md2=4;
int md3=7;
int md4=8;
//variables for Ultrasonic in forward direction
int trigf=3;     
int echof=5; 
long tmf;    
int distf;
//variables for Ultrasonic in left direction
int trigl=6;     
int echol=9; 
long tml;    
int distl;
//variables for Ultrasonic in right direction
int trigr=10;     
int echor=11; 
long tmr;    
int distr;
int counter=0;  
//int led=2;
void setup() 
{
  // put your setup code here, to run once:
  pinMode(md1,OUTPUT);     
  pinMode(md2,OUTPUT);
  pinMode(md3,OUTPUT);     
  pinMode(md4,OUTPUT);
  pinMode(echof,INPUT);    
  pinMode(trigf,OUTPUT);
  pinMode(echol,INPUT);    
  pinMode(trigl,OUTPUT);
  pinMode(echor,INPUT);    
  pinMode(trigr,OUTPUT);
  //pinMode(led,OUTPUT);
  Serial.begin(9600); 
}
int calcf()  // function to calculate and return forward distance
{
  digitalWrite(trigf,LOW);
  delayMicroseconds(2);
  digitalWrite(trigf,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigf,LOW);
  tmf=pulseIn(echof,HIGH);    
  distf=tmf*0.034/2;
  return distf;
}
int calcl()  // function to calculate and return left distance
{
  digitalWrite(trigl,LOW);
  delayMicroseconds(2);
  digitalWrite(trigl,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigl,LOW);
  tml=pulseIn(echol,HIGH);    
  distl=tml*0.034/2;
  return distl;
}
int calcr()  // function to calculate and return right distance
{
  digitalWrite(trigr,LOW);
  delayMicroseconds(2);
  digitalWrite(trigr,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigr,LOW);
  tmr=pulseIn(echor,HIGH);    
  distr=tmr*0.034/2;
  return distr;
}
void forward()
{
  digitalWrite(md1,LOW);
  digitalWrite(md2,HIGH);
  digitalWrite(md3,LOW);
  digitalWrite(md4,HIGH);
  delay(time1);  // If we will give delay than only thing will get some time to move 
}
void left()
{
  digitalWrite(md1,LOW);
  digitalWrite(md2,HIGH);
  digitalWrite(md3,HIGH);
  digitalWrite(md4,LOW);
  delay(time1);   // If we will give delay than only thing will get some time to move 
}
void right()
{
  digitalWrite(md1,HIGH);
  digitalWrite(md2,LOW);
  digitalWrite(md3,LOW);
  digitalWrite(md4,HIGH);
  delay(time1);   // If we will give delay than only thing will get some time to move 
}
void turn()
{
  digitalWrite(md1,HIGH);
  digitalWrite(md2,LOW);
  digitalWrite(md3,LOW);
  digitalWrite(md4,HIGH);
  delay(time2);   // If we will give delay than only thing will get some time to move 
}
void center(int f,int l,int r)  // path to be taken when it guesses that box can be a centre 
{
  if(f==l)
  {
    
  }
  if(f==r)
  {
    
  }
}
void chk0(int f,int l,int r)  // It is for counter 0 prefence -- f,l,r
{
  if(f>7)
  {
    forward();
    //delay   // No need to give delay here because delay already given in forward function
  }
  else if(l>7)
  {
    left();
    //delay   // No need to give delay here because delay already given in left function
  }
  else if(r>7)
  {
    right();
    //delay   // No need to give delay here because delay already given in right function
  }
  else
  {
    turn();
    //delay    // No need to give delay here because delay already given in turn function
  }
  counter++;
}
void chk1(int l,int r,int f)  // It is for counter 1 prefence -- l,r,f
{
  if(l>7)
  {
    left();
    //delay
  }
  else if(r>7)
  {
    right();
    //delay
  }
  else if(f>7)
  {
    forward();
    //delay
  }
  else
  {
    turn();
    //delay
  }
  counter++;
}
void chk2(int r,int f,int l)  // It is for counter 2 prefence -- r,f,l
{
  if(r>7)
  {
    right();
    //delay
  }
  else if(f>7)
  {
    forward();
    //delay
  }
  else if(l>7)
  {
    left();
    //delay
  }
  else
  {
    turn();
    //delay
  }
  counter++;
}
void moverob(int f,int l,int r)
{
  if(f==l||f==r)   // If this condition hold than it will according to path set in center function
  {
    center(f,l,r); 
  }
  else if(f>7&&l<7&&r<7)
  {
    forward();
  }
  else
  {
    if(counter%3==0)
    {
      chk0(f,l,r);
    }
    else if(counter%3==1)
    {
      chk1(l,r,f);
    }
    else if(counter%3==1)
    {
      chk2(r,f,l);
    }
  }
}
void correction(int f,int l,int r)  //correction to path
{
  if(r>l)    //move slight left
  {
    digitalWrite(md1,LOW);
    digitalWrite(md2,HIGH);
    digitalWrite(md3,HIGH);
    digitalWrite(md4,LOW);
    delay(time2);   // If we will give delay than only thing will get some time to move 
  }
  else if(l>r)   //move slight right
  {
    digitalWrite(md1,HIGH);
    digitalWrite(md2,LOW);
    digitalWrite(md3,LOW);
    digitalWrite(md4,HIGH);
    delay(time2);   // If we will give delay than only thing will get some time to move 
  }
}
void setup() 
{
  // put your setup code here, to run once:
  pinMode(md1,OUTPUT);     
  pinMode(md2,OUTPUT);
  pinMode(md3,OUTPUT);     
  pinMode(md4,OUTPUT);
  pinMode(echof,INPUT);    
  pinMode(trigf,OUTPUT);
  pinMode(echol,INPUT);    
  pinMode(trigl,OUTPUT);
  pinMode(echor,INPUT);    
  pinMode(trigr,OUTPUT);
  //pinMode(led,OUTPUT);
  Serial.begin(9600); 
}
void loop() 
{
  // put your main code here, to run repeatedly:
  distf=calcf();
  distl=calcl();
  distr=calcr();
  moverob(distf,distl,distr);
  correction(distf,distl,distr);
}



/* Thing to notice 
See there will be three time. 
time1 == time taken to turn left or right.
time2 == time taken to turn 180.
time3 == time taken to turn slight left or slight right.
*/
