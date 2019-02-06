#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<fcntl.h>
#include<string.h>
#include<unistd.h>

int read_buf;
int main()
{
	int i,fd;
	
	char ch;
       	
do 
{	
	printf("enter x for x-axis reading, y for y-axis reading, z for z-axis reading, press e for exit\n");
	scanf(" %c",&ch);
	switch(ch)
   {
    	case 'x':
        fd=open("/dev/adxl_x", O_RDWR);
        read(fd,&read_buf,sizeof(read_buf));
        printf("x-axis reading =%d\n",read_buf);
        close(fd);
        break;
    	case 'y':
        fd=open("/dev/adxl_y", O_RDWR);
        read(fd,&read_buf,sizeof(read_buf));
        printf("y-axis reading =%d\n",read_buf);
        close(fd);
        break;
    	case 'z':
        fd=open("/dev/adxl_z", O_RDWR);
        read(fd,&read_buf,sizeof(read_buf));
        printf("z-axis reading =%d\n",read_buf);
        close(fd);
        break;
	case 'e':
	printf("Exiting...\n");
	break;
    	default:
        printf("Command not recognized\n");
        break;
   }
}while(ch!='e');

return 0;
}
