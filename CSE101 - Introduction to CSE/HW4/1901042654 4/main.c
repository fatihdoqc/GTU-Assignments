
#include <stdio.h>   /* Standard input/output definitions */
#include <string.h>  /* String function definitions */
#include <windows.h>

void main(void){

    int slct = 0;
    int check = 0;
    int i = 0;
    BOOL Status;

    printf("\n\n ## WELCOME TO GTU ARDUINO LAB        ##");
    printf("\n ## STUDENT NAME: FATIH DOGAC         ## ");
    printf("\n ## PLEASE SELECT FROM THE FOLLOWING  ## \n");
    printf(" ## MENU :                            ## \n");
    printf("(1) TURN ON LED ON ARDUINO\n");
    printf("(2) TURN OFF LED ON ARDUINO \n");
    printf("(3) FLASH ARDUINO LED 3 TIMES \n");
    printf("(4) SEND A NUMBER TO ARDUINO TO COMPUTE SQUARE BY ARDUINO \n");
    printf("(0) EXIT ");

/*---------------OPENED SERIAL PORT-----------------*/

    char whichCOM[6] = "COM3"; //This is the port that I used.

    HANDLE hSerial;
    hSerial = CreateFile(whichCOM,
                GENERIC_READ | GENERIC_WRITE,
                0,
                0,
                OPEN_EXISTING, //This one checks if the file exist.If it is not, then it won't open it.
                FILE_ATTRIBUTE_NORMAL,
                0);

    if(hSerial==INVALID_HANDLE_VALUE){

        if(GetLastError()==ERROR_FILE_NOT_FOUND){
                    printf("serial port does not exist.");
        }
        printf("ERROR CHECK AGAIN");
    }
    /*---------------SETTING PARAMETERS-----------------*/
        DCB dcbSerialParams = {0};
    dcbSerialParams.DCBlength=sizeof(dcbSerialParams);
    if (!GetCommState(hSerial, &dcbSerialParams)) {
            printf("error getting status");
    }

    dcbSerialParams.BaudRate=CBR_9600;
    dcbSerialParams.ByteSize=8;
    dcbSerialParams.StopBits=ONESTOPBIT;
    dcbSerialParams.Parity=NOPARITY;

    Status = SetCommState(hSerial, &dcbSerialParams);

    if(!SetCommState(hSerial, &dcbSerialParams)){
        printf("error setting serial port state");
        }
        /*---------------SETTING TIMEOUTS-----------------*/
        COMMTIMEOUTS timeouts={0};
    timeouts.ReadIntervalTimeout=50;
    timeouts.ReadTotalTimeoutConstant=50;
    timeouts.ReadTotalTimeoutMultiplier=10;
    timeouts.WriteTotalTimeoutConstant=50;
    timeouts.WriteTotalTimeoutMultiplier=10;

    if(!SetCommTimeouts(hSerial, &timeouts)){
        printf("TIMEOUT ERROR");
    }
/*---------------READING/WRITING DATA-----------------*/
    char szBuff[9] = {0};
    DWORD dwBytesRead = 0;

    if(!ReadFile(hSerial, szBuff, 8, &dwBytesRead, NULL)){
       printf("error on reading");
    }
void sendingToPort(HANDLE hSerial ,int command, int number, BOOL Status){ //The function which allows me to sending datas to the serial port in an easy way

        char   lpBuffer[1];
		DWORD  dNoOFBytestoWrite;
		DWORD  dNoOfBytesWritten = 0;
		dNoOFBytestoWrite = sizeof(lpBuffer);

		if(command==1){        //Checking the selection and by its type, I am declearing the byte that I will send to arduino in every situation.
            lpBuffer[0]='x'; //Sending the byte "x" to arduino which is going to open the led
		}else if(command==2){
            lpBuffer[0]='y';//Sending the byte "y" to arduino which is going to close the led
		}else if(command==3){
            lpBuffer[0]='z';//Sending the byte "z" to arduino which is going to flash the led 3 times
        }else if(command==4){
            printf("Couldn't do that one,sorry");

		}
		Status = WriteFile(hSerial,                 //Pointing at my port
						   lpBuffer,                //My byte
						   dNoOFBytestoWrite,
						   &dNoOfBytesWritten,
						   NULL);

		if (Status != TRUE)
			printf("\n\n   Error %d in Writing to Serial Port",GetLastError());
	}
	while(TRUE){    //Provided the menu will be showed until the user shuts it down.
        printf("\nPlease select : ");
        check = scanf("%d" , &slct);    //Program took the selection.

        if(check == 0){ // Provided that the user can only write integers.
            printf("INVALID SELECTION");
            break;
        }
        else if(slct < 0 || slct > 5) // User is allowed to stay between 0 and 5.
        {
            printf("Please enter 0< ""something"" <5");

        }
        else if(check > 0 && check < 5){

            if(slct == 1){ //Open the led.

                sendingToPort(hSerial,slct,0,Status);
            }
            else if(slct == 2){ // Close the led.

                sendingToPort(hSerial,slct,0,Status);
            }
            else if(slct == 3){ // Flash the led 3 times
                sendingToPort(hSerial,slct,0,Status);

            }
             else if(slct == 4){
                printf("Couldn't do that one,sorry");

            }
            else if(slct == 0){
                    break;
                    }
            //Exit.


        }







	}




CloseHandle(hSerial);//Close the port.


}



