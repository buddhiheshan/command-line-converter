//Name	:	PERERA G K B H

#include <stdio.h>

//Declear globle varibles
int i = 0, j = 0;//For counting in loops
int num[6] = {10,11,12,13,14,15};//For mapping hexadecimal numbers
char letter[6] = {'A','B','C','D','E','F'};//For mapping hexadecimal characters

int checkInput(char input,char sign);//To check input arguments
int checkOutput(char output,char sign);//To check output arguments
int getSize(const char arr[]);//To get size of char array
long string2Int(const char arr[], int size);//To convert string to integer
void checkNeg(char sign, int bin[]);//To check negative inputs
void convI2B(int number, int bin[]);//To convert Integer to Binary
void twocomp(int bin[]);//To perform twos compliment on negative numbers
double powerOf(int power, int base);//To get the power of a number
void convB2H(int bin[], int size, int hex[]);//To convert Binary to Hexadecimal
void changeArray(char input, int size, const char argv[], int bin[], int hex[]);//To change array from string to binary or hexadecimal
int convB2I(int bin[], int size);//To convert Binary yo Integer
void convH2B(int hex[], int bin[], int size);//To convert Hexadecimal to Binary
double sring2Double(const char arr[], int size);//To convert string to float or double
void convF2B(long num_int, double num_deci, int bin[], int manti[], int size, int exp_len);//To convert float or double to binary
double convB2F(int bin[], int exp_b[], int exp_size, int size);//To cinvert binary to float or double
int formatAndSizeErr(int form_err, int size_err);//To print format anf size error
int checkInteger(const char arr[], int size);//To check format of integer
int checkIntSize(long number);//To check size of integer
int checkBinary(const char arr[], int size);//To check format of binary
int checkHexa(const char arr[], int size);//To check format of hexadecimal
int checkArrSize(int size, int bit32, int bit64);//To check aarray size
int checkDoubleSize(double number);//To check the float or double in integer range
int checkDouble(const char arr[], int size);//To check format of double or float
void printBin(int binary[], int size);//To print binary array
void printHex(int hexa[], int size);//To print hexadecimal array

int main(int argc, char const *argv[])
{
	//Check for number of arguments
	if ( argc == 4 ){
		//Check for input and output arguments
		if ( ( checkInput( argv[1][1], argv[1][0]) != 0 ) || ( checkOutput( argv[2][1], argv[2][0]) != 0 ) )
			return -1;
		int size = getSize(argv[3]);//Get the size of the input value
		if ( argv[1][1] == 'I' ){//For Integer Input
			int bin[32] = {0}, hex[8] = {0};//Declear arrays for binary and hexadecimal
			long number = string2Int(argv[3], size);//Convert string input to a number
			//Convert negative inputs to negative values
			if ( argv[3][0] == '-' )
				number = number * -1;
			//Check for Size and Format Errors
			if ( formatAndSizeErr(checkInteger(argv[3], size), checkIntSize(number)) != 0 )
				return -1;

			if( argv[2][1] == 'I' )//For Integer Output
				fprintf(stdout, "%d\n", (int)number);

			else if ( argv[2][1] == 'B' ){//for Binary Output
				checkNeg(argv[3][0],bin);//Check if input value is negative
				convI2B(number,bin);//Convert the integer numer into binary
				twocomp(bin);//Twos complement for negative numbers
				printBin(bin,32);//Print the binary array
			}
			else if( argv[2][1] == 'H' ){//For Hexadecimal Output
				checkNeg(argv[3][0],bin);//Check if input value is negative
				convI2B(number,bin);//Convert the integer numer into binary
				twocomp(bin);//Twos complement for negative numbers
				convB2H(bin,8,hex);//Convert Binary into hexadecimal
				printHex(hex,8);//Print hexadecimal array
			}
			else if( argv[2][1] == 'F' )//For Floating Output
				fprintf(stdout,"%.2f\n",(double)number);
			
			else
				fprintf(stderr,"ERROR: This conversion is not possible.\n");
		}
		else if ( argv[1][1] == 'B' ){//For Binary Input
			//Check for Size and Format Errors
			if ( formatAndSizeErr(checkBinary(argv[3], size),checkArrSize(size, 32, 64)) != 0 )
				return -1;

			if ( size == 32 ){//For 32 input size
				int bin[32] = {0}, hex[8] = {0};//Declear arrays for binary and hexadecimal
				changeArray('B',size,argv[3],bin,hex);//Assign values in char array to int arrays
				if ( argv[2][1] == 'I' ){//For Integer Output
					twocomp(bin);//Invert the negative numbers
					int integer=convB2I(bin,31);//Convert Binary into Integer
					if (bin[0]==1)//Make integer number negative if input binary is nagative
						integer=integer * -1;
					fprintf(stdout,"%d\n",integer);//Print the integer
				}
				else if( argv[2][1] == 'F' ){//For Floating Output
					int exp_b[9] = {};//Declear array to copy the exponent part
					printf("%.2f\n", convB2F(bin,exp_b, 8, size));//Convert and print the floating number
				}
				else if( argv[2][1] == 'H' ){//For Hexadecimal Output
					convB2H(bin, size/4, hex);//Convert Binary into Hexadecimal
					printHex(hex, size/4);//Print Hexadecimal array
				}
				else if( argv[2][1] == 'B' )//For Binary Output
					printBin(bin, 32);//Print binary array

				else
					fprintf(stderr, "ERROR: This conversion is not possible.\n");
			}
			if (size==64){//For 64 input size
				int bin[64]={0},hex[16]={0};//Declear arrays for binary and hexadecimal
				changeArray('B',size,argv[3],bin,hex);//Assign values in char array to int arrays
				if (argv[2][1]=='D'){//For Double Output
					int exp_b[12]={};//Declear array to copy the exponent part
					printf("%lf\n",convB2F(bin,exp_b,11,size));//Convert and print the double number
				}
				else if(argv[2][1]=='H'){//For Hexadecimal Output
					convB2H(bin,size/4,hex);//Convert Binary to Hexadecimal
					printHex(hex,size/4);//Print Hexadecimal array
				}
				else if(argv[2][1]=='B')//For Binary Output
					printBin(bin,64);//Print Binary array
				else
					fprintf(stderr,"ERROR: This conversion is not possible.\n");
			}
		}
		else if ( argv[1][1] == 'H' ){//For Hexadecimal Input
			//Check for Size and Format Errors
			if (formatAndSizeErr(checkHexa(argv[3],size),checkArrSize(size,8,16))!=0)
				return -1;

			if (size==8){//For 8 digit hexadecimal
				int bin[32]={0},hex[8]={0};//Declear arrays for binary and hexadecimal
				changeArray('H',size,argv[3],bin,hex);//Assign values in char array ti int array
				if (argv[2][1]=='I'){//For Integer Output
					convH2B(hex,bin,size);//Convert Hexadecimal to binary
					twocomp(bin);//Twos complement for negative numbers
					int integer=convB2I(bin,31);//Convert binary to integer and assign to another variable
					if (bin[0]==1)//Make integer number negative if input binary is nagative
						integer = integer * -1;
					fprintf(stdout,"%d\n",integer);//Print the integer output
				}
				else if(argv[2][1] == 'F'){//For floating output
					convH2B(hex,bin,size);//Convert hexadecimal to binary
					int exp_b[9]={};//Declear array to copy exponent part
					printf("%.2lf\n",convB2F(bin,exp_b,8,32));//Convert binary to float and print floating number 
				}
				else if(argv[2][1] == 'B'){//For binary output
					convH2B(hex,bin,size);//Convert hexadecimal to binary
					printBin(bin,size*4);//Print binary array
				}
				else if(argv[2][1] == 'H')//For Hexadecimal output
					printHex(hex,8);//Print hexadecimal array
				else
					fprintf(stderr,"ERROR: This conversion is not possible.\n");
			}
			if (size==16){//For 16 digit hexadecimal
				int bin[64]={0},hex[16]={0};//Declear array for binary and hexadecimal
				changeArray('H',size,argv[3],bin,hex);//Assign char array to int array
				if (argv[2][1]=='D'){//For double output
					convH2B(hex,bin,size);//Convert hexadecimal to binary
					int exp_b[12]={};//Declear array to copy exponent part
					printf("%lf\n",convB2F(bin,exp_b,11,64));//Convert binary to double and print double output
				}
				else if(argv[2][1]=='B'){//For binary output
					convH2B(hex,bin,size);//Convert hexadecimal to binary
					printBin(bin,size*4);//Print binary array
				}
				else if(argv[2][1]=='H')//For hexadecimal output
					printHex(hex,16);//Print hexadecimal array
				else
					fprintf(stderr,"ERROR: This conversion is not possible.\n");
			}
		}
		else if ( argv[1][1] == 'F' ){//For Floating input
			double number=sring2Double(argv[3],size);//Convert string to float
			long num_int=(long)number;//Get the integer part of the float number
			float num_deci=number-num_int;//Get the decimal part of the float number
			//Check for size and format errors
			if (formatAndSizeErr(checkDouble(argv[3],size),0)!=0)
				return -1;
			
			int bin[32]={0},manti[32]={0};//Declear array for binary and mantissa part

			if (argv[2][1]=='I'){//For Integer output				
				if (argv[3][0]=='-')//Make integer number negative if input binary is nagative
					number=number*-1;

				if ((checkDoubleSize(number))!=0){//Error if float is not in integer range
					fprintf(stderr,"ERROR: This conversion is not possible.\n");
					return -1;
				}
				
				fprintf(stderr,"WARNING: There is a possibility for a precision loss.\n");
				fprintf(stdout,"%d\n",(int)number);//Print the integer output
			}
			
			else if(argv[2][1]=='F'){//For Floating output
				if (argv[3][0]=='-'){//If the number is negative
					fprintf(stdout, "-");
					fprintf(stdout, "%.2f\n",number);
				}
				else//If the number is positive
					fprintf(stdout, "%.2f\n",number);
			}

			else if(argv[2][1]=='B'){//For Binary output
				if (number==0)//When the input number is 0
					printBin(bin,32);//Print zero array
				else{
					convF2B(num_int,num_deci,bin,manti,31,8);//Convert Floating to Binary
					checkNeg(argv[3][0],bin);//Check if the input number is neagtive
					printBin(bin,32);//Print Binary Array
				}
			}
			else if(argv[2][1]=='H'){//For Hexadecimal output
				int hex[8]={0};//Declear array for hexa decimal
				if (number==0)//When the input number is 0
					printHex(hex,8);//Print zero array
				else{
					convF2B(num_int,num_deci,bin,manti,31,8);//Convert float to Binary
					checkNeg(argv[3][0],bin);//Check if the input number is negative
					convB2H(bin,8,hex);//Convert binary to hexadecimal 
					printHex(hex,8);//Print hexadecimal array
				}
			}
			else
				fprintf(stderr,"ERROR: This conversion is not possible.\n");
		}
		else if ( argv[1][1] == 'D' ){//For double output
			double number=sring2Double(argv[3],size);//Convert string to double
			int num_int=(int)number;//Get integer part of double number
			double num_deci=number-num_int;//Get decimal part of double number
			//Check for size and format errors
			if (formatAndSizeErr(checkDouble(argv[3],size),0)!=0)
				return -1;

			int bin[64]={0},manti[64]={0};//Declear arrays for binary and mantissa

			if(argv[2][1]=='D'){//For Double output
				if (argv[3][0]=='-'){//If input number is negative
					fprintf(stdout, "-");
					fprintf(stdout, "%lf\n",number);
				}
				else//If input number is positive
					fprintf(stdout, "%lf\n",number);
			}

			else if(argv[2][1]=='B'){//For binary output
				if (number==0)//When input number is 0
					printBin(bin,64);//Print zero array
				else{
					convF2B(num_int,num_deci,bin,manti,63,11);//Convert double to binary
					checkNeg(argv[3][0],bin);//Check for negative input
					printBin(bin,64);//Print binary array
				}
			}
			else if(argv[2][1]=='H'){//For hexadecimal output
				int hex[16]={0};//Declear array for hexadecimal
				if (number==0)//When input number is 0
					printHex(hex,16);//Print hexadecimal array
				else{
					convF2B(num_int,num_deci,bin,manti,63,11);//Convert double to binary
					checkNeg(argv[3][0],bin);//Check for negative numbers
					convB2H(bin,16,hex);//Convert binary to hexadecimal
					printHex(hex,16);//Print hexadecimal array
				}
			}
			else//For integer and floating outputs
				fprintf(stderr,"ERROR: This conversion is not possible.\n");
		}
	}
	else{
		//Wrong number of arguments
		fprintf(stderr,"ERROR: The number of arguments is wrong.\nUsage: ./clc -<input format> -<output format> <input>\n");
	}
	return 0;
}

int checkInput(char input, char sign)//To check the input arguments
{
	if ( ((input=='I')||(input=='B')||(input=='H')||(input=='F')||(input=='D')) && (sign=='-') )
		return 0;
	fprintf(stderr,"ERROR: The input argument is wrong.\nPossible input arguments are -B, -H, -I, -F and -D.\n");
	return -1;
}

int checkOutput(char output, char sign)//TO check the output arguments
{
	if ( ((output=='I')||(output=='B')||(output=='H')||(output=='F')||(output=='D')) && (sign=='-') )
		return 0;
	fprintf(stderr,"ERROR: The output argument is wrong.\nPossible output arguments are -B, -H, -I, -F and -D.\n");
	return -1;
}

int getSize(const char arr[])//To get the size
{
	int	size=0;//Declear a variable for size
	while (arr[size]!='\0'){//Loop until the char array ends 
		size++;
	}
	return size;
}

long string2Int(const char arr[],int size)//To convert string to integer
{
	long integer=0;//Declear variable to store the integer
	if (arr[0]=='-'){//For negative numbers
		for (i=1;i<size;i++)
			integer=(integer*10)+arr[i]-'0';
	}
	else{//For positive integers
		for (i=0;i<size;i++)
			integer=(integer*10)+arr[i]-'0';
	}
	return integer;
}

void checkNeg(char sign, int bin[])//To check the negative inputs
{
	if (sign=='-')//If negaitve assign most significant bit as 1 in binary array
		bin[0]=1;
}

void convI2B(int number,int bin[])//To convert integer to binary
{
	for (i=31;i>0;i--){
		bin[i]=number%2;
		number=number/2;
	}
}

void twocomp(int bin[])//To handle nagative numbers
{
	if (bin[0]==1){//Invert the array if the number is negative
		for (i=31;i>0;i--){
			if (bin[i]==0)
				bin[i]=1;
			else
				bin[i]=0;
		}
		bin[31]++;//Add 1 to the inverted array
		for (i=31;i>0;i--){//Handle the carry
			if (bin[i]>1){
				bin[i]=0;
				bin[i-1]++;
			}
		}
		if (bin[0]>1)//Correct the error in the first bit after handling the carry
			bin[0]=1;
	}
}

double powerOf(int power,int base)//To get the power a number
{
	if (power==0)//When power is 0
		return 1;
	if (power==1)//When power is 1
		return base;
	return base*powerOf(power-1,base);
}

void convB2H(int bin[],int size,int hex[])//To convert binary to hexadecimal
{
	for (i=0;i<(size);i++){//Group into 4 bit groups
		double power=3;//Declear variable to get power
		for (j=i*4;j<((i+1)*4);j++){
			hex[i]=hex[i]+bin[j]*powerOf(power,2);
			power--;
		}
	}
}

void changeArray(char input,int size,const char argv[],int bin[],int hex[])//To change array from string to binary or hexadecimal
{
	if (input=='B'){//When the input array is binary
		for (i=size-1;i>=0;i--){
			if (argv[i]=='0')
				bin[i]=0;
			else
				bin[i]=1;
		}
	}
	else{
		for (i=0;i<(size);i++){//When the input array is hexadecimal
			if ((argv[i]>='0') && (argv[i]<='9'))//For hexadecimal characters less than 10
				hex[i]=argv[i]-'0';
			else{//For hexadecimal characters greater than 9
				for (j=0;j<7;j++){
					if (argv[i]==letter[j])
						hex[i]=num[j];
				}
			}
		}
	}
}

int convB2I(int bin[],int size)//To convert binary to integer
{
	double power=0,integer;//Declear variables
	for (i=size;i>0;i--){
		integer=integer+bin[i]*powerOf(power,2);//Take the sum of the binary bit muliplied by the place values
		power++;
	}
	return integer;
}

void convH2B(int hex[],int bin[],int size)//To convert hexdecimal to binary
{
	for (i=0;i<(size);i++){
		//Take each element in hexa array and split into binary groups of 4 depending on the place values in binary
		for (j=((i+1)*4)-1;j>=i*4;j--){
			bin[j]=hex[i]%2;
			hex[i]=hex[i]/2;
		}
	}
}

double sring2Double(const char arr[],int size)//To convert string to float or double
{
	//Declear variables
	long integer=0;
	double decimal=0;
	int count=0;
	if (arr[0]=='-'){//When input is a negative number
		count=1;
		while (arr[count]!='.'){//Identify the decimal point
			if (count==size)
				break;
			count++;
		}
		for (i=1;i<count;i++){//Identify adn get the integer part
			integer=(integer*10)+arr[i]-'0';
		}
	}
	else{//When the input is a positive number
		while (arr[count]!='.'){//Identify the decimal point
			if (count==size)
				break;
			count++;
		}
		for (i=0;i<count;i++){//Identify and get the integer part
			integer=(integer*10)+arr[i]-'0';
		}
	}
	count++;
	for (i=size-1;i>=count;i--){//Get the decimal part
		decimal=decimal/10+(((double)arr[i]-'0')/10);
	}
	return (integer+decimal);
}

void convF2B(long num_int,double num_deci,int bin[],int manti[],int size,int exp_len)//To convert float or double to binary
{
	//int manti[32]={};//Declear a array to store the mantissa part of the IEEE754 format
	//Assign the binary converted integer part of the float to mantissa array from back of the array
	for (i=size;i>=0;i--){
		manti[i]=num_int%2;
		num_int=num_int/2;
	}
	int count=0;//Declear a variable to identify the starting 1 of the integer part of float stored in array 
	while (manti[count]==0){
		count++;
		if (count==size) break;
	}
	//Assign the integer part to the matissa array starting from the begining of the arrat
	for (i=count;i<=size;i++){
		manti[i-count]=manti[i];
	}
	int decimal=size-count;//Declear a variable to store the bit before the decimal point
	//Assign the binary converted decimal part of the float to mantissa array
	for (i=decimal+1;i<=size;i++){
		if ((num_deci*2)>=1){
			manti[i]=1;
			num_deci=num_deci*2-1;
		}
		else{
			manti[i]=0;
			num_deci=num_deci*2;
		}
	}
	//Find the starting 1 of the mantissa array
	count=0;
	while (manti[count]==0){
		count++;
		if (count==size) break;
	}
	//Assign the mantissa part of the floating number to the bin array
	for (i=exp_len+1;i<=size;i++){
		bin[i]=manti[count + i - exp_len];
	}

	//Declear a variable for exponent, convert and assign the exponent to the bin array
	int exp=(powerOf(exp_len-1,2)-1)+decimal-count;
	for (i=exp_len;i>0;i--){
		bin[i]=exp%2;
		exp=exp/2;
	}
}

double convB2F(int bin[],int exp_b[],int exp_size,int size)//To convert binary to float or double
{
	//int exp_b[exp_size+1]={};//Declear an array to copy the exponent part of the binary number
	for (i=1;i<(exp_size+1);i++){
		exp_b[i]=bin[i];
	}
	int exp=convB2I(exp_b,exp_size)-((powerOf(exp_size-1,2))-1);//Declear and assign the converted exponent from binary to intger
	double mantissa=0;//Declear a variable to store the value of mantissa
	for (i=exp_size+1;i<size;i++){
		mantissa=mantissa+(bin[i]*(1/(powerOf(i-exp_size,2))));
	}
	if (exp<0)
		return powerOf(bin[0],-1)*(1+mantissa)*(1/powerOf(-1*exp,2));
	else
		return powerOf(bin[0],-1)*(1+mantissa)*powerOf(exp,2);//Return the float number
}

int formatAndSizeErr(int form_err,int size_err)//To print respective error
{
	if (form_err!=0){//For format error
		fprintf(stderr,"ERROR: Input format error at location %d.\n",form_err-1);
		return -1;
	}
	if (size_err!=0){//For size error
		fprintf(stderr,"ERROR: The input size is wrong.\n");
		return -1;
	}
	return 0;
}

int checkInteger(const char arr[],int size)//To check the format of integer
{
	if (arr[0]=='-'){//For negative integers
		for (i=1;i<size;i++)
			if ( ( (arr[i])<'0') || (arr[i]>'9') )
				return i+1;
	}
	else{//For positive integers
		for (i=0;i<size;i++)
			if ( (arr[i]<'0') || (arr[i]>'9') )
				return i+1;	
	}
	return 0;
}

int checkIntSize(long number)//To check size of integers
{
	if ((number>2147483647) || (number<-2147483648))//Check the range
		return -1;
	return 0;
}

int checkBinary(const char arr[],int size)//To check the format of binary
{
	for (i=0;i<size;i++)
		if ( (arr[i]!='0') && (arr[i]!='1'))//Check for valid digits
			return i+1;
	return 0;
}

int checkHexa(const char arr[],int size)//To check the format of hexadecimal
{
	for (i=0;i<size;i++)
		if ( ((arr[i]<'0') || (arr[i]>'9')) && ((arr[i]<'A') || (arr[i]>'F')) )//Check for valid digits and letters
			return i+1;
	return 0;
}

int checkArrSize(int size,int bit32,int bit64)//TO check the array size
{
	if ((size!=bit32) && (size!=bit64)==1)//Check is the size is 32 or 64
		return -1;
	return 0;
}

int checkDoubleSize(double number)//To chek the float in integer range
{
	if ((number>2147483647) || (number<-2147483648))//Check the range of integer
		return -1;
	return 0;
}

int checkDouble(const char arr[],int size)//To check the format of float and double
{
	int point=0;//Declear and initialize a variable to get the number if decimal points
	if (arr[0]=='-'){//For negative inputs
		for (i=1;i<size;i++){
			if ( ((arr[i]<'0') || (arr[i]>'9')) && (arr[i]!='.'))//Check array for invalid digits
				return i+1;	
			if (arr[i]=='.'){//Check for decimal points
				point++;}
			if (point>1)//Check for more than 1 decimal point
				return i+1;
		}
	}
	else{//For positive inputs
		for (i=0;i<size;i++){
			if ( ((arr[i]<'0') || (arr[i]>'9')) && (arr[i]!='.'))//Check array for invalid digits
				return i+1;	
			if (arr[i]=='.'){//Check for decimal points
				point++;}
			if (point>1)
				return i+1;//Check for more than 1 decimal point
		}
	}
	return 0;
}

void printBin(int binary[],int size)//To print binary array
{
	for (i=0;i<size;i++)
		fprintf(stdout,"%d",binary[i]);
	printf("\n");
}

void printHex(int hexa[],int size)
{
	fprintf(stdout,"0x");
	for ( i = 0;i < (size);i++){
		if (hexa[i] <10 )//Print hexadecimal value if it is less than 10
			printf("%d",hexa[i]);
		//For hexadecimal values greater than 9, map the corresponding number to the value
		else{
			for ( j = 0;j < 7;j++){
				if (num[j] == hexa[i])
					fprintf(stdout,"%c",letter[num[j]-10]);
			}
		}
	}
	fprintf(stdout,"\n");
}