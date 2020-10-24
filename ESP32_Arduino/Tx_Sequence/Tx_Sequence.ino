#define const_size 64000

int var1 = 4900;
int var2 = 9216;
int var3 = 25600;
int var4 = 50176;
int var5 = 129600;
int var6 = 193600;
int var7 = 262144;
int var8 = 360000;
int var9 = 480000;
int var10 = 560000;
int var11 = 640000;
int var12 = 720000;
int var13 = 810000;
int var14 = 880000;
int var15 = 960000;

void array_gen(char* arrays,int array_size)
{
  int i=0;
  for(i=0;i<array_size;i++)
  {
    arrays[i] = 128;
  }
  arrays[i+1]='\0';
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Hello World!");
}

char array1[const_size];

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("Testme\n");
  delay(5000);

  array_gen(array1,var1);
  Serial.println(array1);
  
}
