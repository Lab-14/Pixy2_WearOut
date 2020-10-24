
#define const_size 64000

char array_gen(int size)
{
	int i=0;
	char image_array[const_size];
	for(i=1;i<=size;i++)
	{
		image_array[i] = 128;
	}

return image_array;

}

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


void transmit_sequence()
{

char array1[const_size] = 0;

int diff_var1;
int diff_var2;

int tx_index = 0;

	// Case-1
	array1 = array_gen(var1);
	serial.print(array1);

	// 5-second delay
	delay_ms(5000);

	// Case-2
	array1 = array_gen(var2);
	serial.print(array1);

	// 5-second delay
	delay_ms(5000);

	// Case-3
	array1 = array_gen(var3);
	serial.print(array1);

	// 5-second delay
	delay_ms(5000);

	// Case-4
	array1 = array_gen(var4);
	serial.print(array1);

	// 5-second delay
	delay_ms(5000);

	// Case-5
	// diff_var1 = var5 - const_size;
	// diff_var2 = diff_var1 - const_size;
	diff_var2 = var5 - 2*const_size;
	array1 = array_gen(const_size);
	for(tx_index=1;tx_index<=2;tx_index++)
	{
		serial.print(array1);		
	}
	array1 = array_gen(diff_var2);
	serial.print(array1);
	
	// 5-second delay
	delay_ms(5000);

	// Case-6
	diff_var2 = var6 - 3*const_size;
	array1 = array_gen(const_size);
	for(tx_index=1;tx_index<=3;tx_index++)
	{
		serial.print(array1);		
	}
	array1 = array_gen(diff_var2);
	serial.print(array1);

	// 5-second delay
	delay_ms(5000);

	// Case-7
	diff_var2 = var7 - 4*const_size;
	array1 = array_gen(const_size);
	for(tx_index=1;tx_index<=4;tx_index++)
	{
		serial.print(array1);		
	}
	array1 = array_gen(diff_var2);
	serial.print(array1);

	// 5-second delay
	delay_ms(5000);

	// Case-8
	diff_var2 = var8 - 5*const_size;
	array1 = array_gen(const_size);
	for(tx_index=1;tx_index<=5;tx_index++)
	{
		serial.print(array1);		
	}
	array1 = array_gen(diff_var2);
	serial.print(array1);

	// 5-second delay
	delay_ms(5000);

	// Case-9
	diff_var2 = var9 - 7*const_size;
	array1 = array_gen(const_size);
	for(tx_index=1;tx_index<=7;tx_index++)
	{
		serial.print(array1);		
	}
	array1 = array_gen(diff_var2);
	serial.print(array1);

	// 5-second delay
	delay_ms(5000);

	// Case-10
	diff_var2 = var10 - 8*const_size;
	array1 = array_gen(const_size);
	for(tx_index=1;tx_index<=8;tx_index++)
	{
		serial.print(array1);		
	}
	array1 = array_gen(diff_var2);
	serial.print(array1);

	// 5-second delay
	delay_ms(5000);

	// Case-11
	diff_var2 = var11 - 10*const_size;
	array1 = array_gen(const_size);
	for(tx_index=1;tx_index<=10;tx_index++)
	{
		serial.print(array1);		
	}
	// array1 = array_gen(diff_var2);
	// serial.print(array1);

	// 5-second delay
	delay_ms(5000);

	// Case-12
	diff_var2 = var12 - 11*const_size;
	array1 = array_gen(const_size);
	for(tx_index=1;tx_index<=11;tx_index++)
	{
		serial.print(array1);		
	}
	array1 = array_gen(diff_var2);
	serial.print(array1);

	// 5-second delay
	delay_ms(5000);

	// Case-13
	diff_var2 = var13 - 12*const_size;
	array1 = array_gen(const_size);
	for(tx_index=1;tx_index<=12;tx_index++)
	{
		serial.print(array1);		
	}
	array1 = array_gen(diff_var2);
	serial.print(array1);

	// 5-second delay
	delay_ms(5000);

	// Case-14
	diff_var2 = var14 - 13*const_size;
	array1 = array_gen(const_size);
	for(tx_index=1;tx_index<=13;tx_index++)
	{
		serial.print(array1);		
	}
	array1 = array_gen(diff_var2);
	serial.print(array1);

	// 5-second delay
	delay_ms(5000);

	// Case-15
	diff_var2 = var15 - 15*const_size;
	array1 = array_gen(const_size);
	for(tx_index=1;tx_index<=15;tx_index++)
	{
		serial.print(array1);		
	}
	// array1 = array_gen(diff_var2);
	// serial.print(array1);

	// 5-second delay
	delay_ms(5000);

}



void loop()
{
	transmit_sequence();	
}

