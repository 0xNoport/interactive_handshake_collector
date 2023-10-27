#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Network {
	char bssid[100];
	char essid[100];
	int channel;
};

struct Network getNetwork(int line) {
	struct Network network;
	
	// Command: cat wifi-netzwerke | head -n 1 | tail -n 1

	char command[50];
	command[0] = '\0';

	// Convert int to string
	char numberAsString[10];
	numberAsString[0] = '\0';
	sprintf(numberAsString, "%d", line);

	// Build the command
	strcpy(command, "cat wifi-netzwerke | head -n ");
	strcat(command, numberAsString);
	strcat(command, " | tail -n 1");

	// Execute the command
	FILE *fp;
	char output[2048];
	output[0] = '\0';
	fp = popen(command, "r");
	while (fgets(output, sizeof(output), fp) != NULL) {

	}
	pclose(fp);
	printf("Output: %s\n", output);

	//Für gleich !!!!!! DENK DARAN DIE 3 bei head durch den int (argument) auszutauschen
	// Get BSSID: cat wifi-netzwerke | awk '{print $1}' | head -n 1 | tail -n 1 | tr -d '\n'
	// Get ESSID: cat wifi-netzwerke | awk '{print $2}' | head -n 1 | tail -n 1 | tr -d '\n'
	// Get Channel: cat wifi-netzwerke | awk '{print $4}' | head -n 1 | tail -n 1 | tr -d '\n'


	// Craft command for BSSID: 
	char commandBSSID[500];
	strcpy(commandBSSID, "cat wifi-netzwerke | awk '{print $1}' | head -n ");
	strcat(commandBSSID, numberAsString);
	strcat(commandBSSID, " | tail -n 1 | tr -d '\n'");
	//printf("\nBSSID COMMAND: %s\n", commandBSSID);

	FILE *fpBSSID;
	char bufferBSSID[25];
	bufferBSSID[0] = '\0',
	fpBSSID = popen(commandBSSID, "r");
	while (fgets(bufferBSSID, sizeof(bufferBSSID), fpBSSID) != NULL) {

	}
	pclose(fpBSSID);
	strcpy(network.bssid, bufferBSSID);

	// Craft command for ESSID: 
	char commandESSID[500];
	strcpy(commandESSID, "cat wifi-netzwerke | awk '{print $2}' | head -n ");
	strcat(commandESSID, numberAsString);
	strcat(commandESSID, " | tail -n 1 | tr -d '\n'");
	//printf("ESSID COMMAND: %s\n", commandESSID);

	FILE *fpESSID;
	char bufferESSID[35];
	bufferESSID[0] = '\0';
	fpESSID = popen(commandESSID, "r");
	while (fgets(bufferESSID, sizeof(bufferESSID), fpESSID) != NULL) {

	}
	pclose(fpESSID);
	strcpy(network.essid, bufferESSID);

	// Craft command for channel: //cat wifi-netzwerke | head -n 4 | tail -n 1 | grep -oE '\s+[0-9]{1,2}\s+' | head -n 1 | tail -n 1 | grep -oE "[0-9]{1,2}" | head -n 1 | tr -d '\n'

	char commandCHANNEL[500];
	commandCHANNEL[0]='\0';
	strcpy(commandCHANNEL, "cat wifi-netzwerke | head -n ");
	strcat(commandCHANNEL, numberAsString);
	strcat(commandCHANNEL, " | tail -n 1 | grep -oE '\\s+[0-9]{1,2}\\s+' | head -n 1 | tail -n 1 | grep -oE \"[0-9]{1,2}\" | head -n 1 | tr -d '\n'");
	//printf("CHANNEL COMMAND: %s\n", commandCHANNEL);

	FILE *fpCHANNEL;
	char bufferCHANNEL[5];
	bufferCHANNEL[0]='\0';
	fpCHANNEL = popen(commandCHANNEL, "r");
	while (fgets(bufferCHANNEL, sizeof(bufferCHANNEL), fpCHANNEL) != NULL) {
		
	}
	pclose(fpCHANNEL);
	
	
	int temp = atoi(bufferCHANNEL);
	network.channel = temp;


	printf("\n\n\n");
	printf("BSSID: %s\n", network.bssid);
	printf("ESSID: %s\n", network.essid);
	printf("CHANNEL: %d\n", network.channel);

	return network;
}

int getAmountOfWifiNetworks() {
	FILE *fp;
	char buffer[50];
	buffer[0] = '\0';
	fp = popen("cat wifi-netzwerke | wc -l", "r");
	while (fgets(buffer, sizeof(buffer), fp) != NULL) {

	}
	//printf("Amount of networks: %d\n", atoi(buffer));
	pclose(fp);
	return atoi(buffer);	
}

int main() {

	// Save list of available wifi networks inside file: wifi-netzwerke
	system("nmcli device wifi list | tail -n +2 | tee wifi-netzwerke");
	const int amountOfNetworks = getAmountOfWifiNetworks();

	//Prompting the user for input:
	printf("Please enter a number");
	int input;
	if (scanf("%d", &input) != 1) {
		printf("\n failed");
		exit(1);
	}

	struct Network network = getNetwork(input);

	char channelAsString[30];
	channelAsString[0] = '\0';
	sprintf(channelAsString, "%d", network.channel);

	//Craft command      // /home/kali/3 bssid channel essid 
	char command[500];
	strcpy(command, "/home/kali/3 ");
	strcat(command, network.bssid);
	strcat(command, " ");
	strcat(command, channelAsString);
	strcat(command, " ");
	strcat(command, network.essid);
	printf("\nThis will be executed: %s", command);
	//sleep(20);

	system(command);



}


