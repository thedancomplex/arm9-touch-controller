#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

/*
	I keep the file descriptors in memory to speed up transactions.
*/
FILE *accel_input_x_scale;
FILE *accel_input_x_raw;
FILE *accel_input_y_scale;
FILE *accel_input_y_raw;
FILE *accel_input_z_scale;
FILE *accel_input_z_raw;

/*
	Initializes the library. It returns true if the lib was initialized properly, and false if it was unable to.
*/
bool accel_init(void){
	accel_input_x_scale = fopen("/sys/bus/i2c/devices/0-0019/iio:device1/in_accel_x_scale","r");
	accel_input_x_raw = fopen("/sys/bus/i2c/devices/0-0019/iio:device1/in_accel_x_raw","r");

	accel_input_y_scale = fopen("/sys/bus/i2c/devices/0-0019/iio:device1/in_accel_y_scale","r");
	accel_input_y_raw = fopen("/sys/bus/i2c/devices/0-0019/iio:device1/in_accel_y_raw","r");

	accel_input_z_scale = fopen("/sys/bus/i2c/devices/0-0019/iio:device1/in_accel_z_scale","r");
	accel_input_z_raw = fopen("/sys/bus/i2c/devices/0-0019/ii:device1/in_accel_z_raw","r");

	return(accel_input_x_scale!=NULL &&
			accel_input_x_raw!=NULL &&
			accel_input_y_scale!=NULL &&
			accel_input_y_raw!=NULL &&
			accel_input_z_scale!=NULL &&
			accel_input_z_raw!=NULL);
}
/*
	Helper function that reads a accel_input*_scale file and returns its' value in double format.
*/
double accel_get_double(FILE* fin){
	char buf[12];
	return atof(fgets(buf,11,fin));
}

/*
	Helper function that reads a accel_input*_raw file and returns its' value in integer format.
*/
double accel_get_int(FILE* fin){
	char buf[8];
	return atoi(fgets(buf,7,fin));
}

/*
	Each of the following functions get the different axis's values in scale or raw.
*/
double accel_get_x_scale(){
	return accel_get_double(accel_input_x_scale);
}

int accel_get_x_raw(){
	return accel_get_int(accel_input_x_raw);	
}

double accel_get_y_scale(){
	return accel_get_double(accel_input_y_scale);
}

int accel_get_y_raw(){
	return accel_get_int(accel_input_y_raw);
}

double accel_get_z_scale(){
	return accel_get_double(accel_input_z_scale);
}

int accel_get_z_raw(){
	return accel_get_int(accel_input_z_raw);
}

/*
	Closes down the library and frees up the no longer needed resources.
*/
void accel_close(){
	if(accel_input_x_scale!=NULL)
		free(accel_input_x_scale);

	if(accel_input_x_raw!=NULL)
		free(accel_input_x_raw);

	if(accel_input_y_scale!=NULL)
		free(accel_input_y_scale);

	if(accel_input_y_raw!=NULL)
		free(accel_input_y_raw);

	if(accel_input_z_scale!=NULL)
		free(accel_input_z_scale);

	if(accel_input_z_raw!=NULL)
		free(accel_input_z_raw);
}

/*
	Simple main. It gets the data and prints it out.
*/

int main(int argc,char *argv[]){
	accel_init();
	for(int i=0;i<20;i++){
		double x = accel_get_x_scale();
		double y = accel_get_y_scale();
		double z = accel_get_z_scale();
		
		printf("X:\t%f\nY:\t%f\nZ:\t%f\n",x,y,z);
	}
	
	accel_close();
	return -1;	
}
