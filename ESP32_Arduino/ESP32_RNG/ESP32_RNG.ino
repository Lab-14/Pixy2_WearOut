
//int randomNumber;
int i;

void setup() {
 
Serial.begin(115200);
randomSeed(42);   
     
}


long rand_array(long size)
{
  long array_rng[size];

  for (i=1;i<size+1;i++)
  {
  array_rng = random(0,256);
  }
}

long tx_array[1000];

void loop() {
 
  //while(i =0, i < 50, i++){
  //  randomNumber = random(0,256);
  
  tx_array[] = rand_array(1000);
  Serial.print("The Random Number sequence is = ");
  Serial.print(tx_array);
  delay(1000);
  
//  }

}
