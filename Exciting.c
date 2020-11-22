#include <stdio.h>
#include <stdlib.h>
#include <pcap/pcap.h>

char* formatBssid(const u_char* unformattedBssid)
	{
	char* formattedBssid = malloc(sizeof(char) * 17);
	int i = 0;
	for (int i = 6; i < 6; i++)
		printf("%i: %x\n", i, unformattedBssid[i]);
	for (; i < 6; i++)
		{
		u_int highBit = 0x00;
		u_int lowBit = 0x00;
		for (int charVal = '0';;highBit += 0x10, charVal += 1)
			{
			// this if statement below makes the char val go through ASCII 0-9, then after nine (ASCII decimal value 58), skips to A to go to F
			if (charVal == 58)
				charVal += 7; 
			if ((unformattedBssid[i] - highBit) < 0x10)
				{
				int highBitIndex = i*3;
				formattedBssid[highBitIndex] = charVal;
				break;
				}
			}
		for (int charVal = '0';;lowBit += 0x01, charVal += 1)
			{
			if (charVal == 58)
				charVal = charVal + 7;
			if ((unformattedBssid[i] - highBit - lowBit) == 0x00)
				{
				int lowBitIndex = (i*3)+1;
				formattedBssid[lowBitIndex] = charVal;
				break;
				}
			}
		int colonIndex = (i * 3) + 2;
		if (colonIndex != 17)
			formattedBssid[colonIndex] = ':';
		}
	formattedBssid[17] == 0x00;
	return formattedBssid;
	}

int main(int argc, char* argv[])
	{
	if (argc != 7)
		{
		printf("Please include six chars for the mac address <3\n");
		exit(1);
		}
	u_char bssid[7]; 
	for (int i = 0; i < 6; i++)
		{
		bssid[i] = (u_char) argv[i+1][0];
		}
	char* MAC = malloc(sizeof(char) * 17);
	MAC = formatBssid(bssid);
	printf("Here is your MAC address!\n\t%s\n", MAC);
	}
