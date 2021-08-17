#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#define VERSIONE 1

using namespace std;

void phome ();
int shome();

void sopzioni(int s);

void startwifi();
void stopwifi();
void statuswifi();
void settingwifi();


void setcolor(unsigned short color)
	{
    HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hCon,color);
	}
			
int main(int argc, char *argv[])
	{
	int s;	
	
	setcolor(7);
	do 
		{
		s=shome();
		sopzioni(s);
		
		printf("\n\n\n");
		system("CLS");
		}
	while (s!=0);
	return 0;
	}


void phome ()
	{
	printf("       / Programma di Antonio Riccio 5H /\n");
	printf("      //////////////////////////////////\n");
	printf("     /             Wi-fi Home         /\n");
	printf("    /            Versione: %d         /\n",VERSIONE);
	printf("   /________________________________/\n");
	}
	

int shome ()
	{
	int s;	

	do
		{	
		phome();
		setcolor(2);
		printf("1) Start\n");
		setcolor(4);
		printf("2) Stop\n");
		setcolor(3);
		printf("3) Status\n");
		setcolor(6);
		printf("4) Setting\n");
		setcolor(7);
		printf("0) Exit\n");
		printf("Opzione: ");
		scanf("%d",&s);
		system("CLS");
		}
	while (s<0 || s>4);	
	}
	

void sopzioni(int s)
	{
	switch (s)
		{
		case 1:
			{
			startwifi();	
			break;
			}
		
		case 2:
			{
			stopwifi();
			break;
			}
			
		case 3:
			{
			statuswifi();	
			break;
			}
			
		case 4:
			{
			settingwifi();
			break;
			}	
		}
	}
		

void startwifi()
	{
	FILE *set;
	int s;
	set=fopen ("setting.bat","r");

	system("CLS");
	printf("       / Programma di Antonio Riccio 5H /\n");
	setcolor(2);
	printf("      //////////////////////////////////\n");
	printf("     /             Wi-fi Start        /\n");
	setcolor(7);
	printf("    /            Versione: %d         /\n",VERSIONE);
	setcolor(2);
	printf("   /________________________________/\n\n");
	setcolor(7);

	if (set==NULL)
		{
		printf("Non sono presenti file di configurazione\n");	
		printf("Vuoi crearli ora ?\n");
		setcolor(2);
		printf("1=YES ");	
		setcolor(4);
		printf("0=NO\n");
		setcolor(7);
		printf("Opzione: ");
		do
			{
			scanf("%d",&s);
			}
		while(s<0 || s>1);
		
		if (s==1)
			{
			settingwifi();
			setcolor(2);
			printf(" La rete wifi sta per essere avviata \n\n ");
			setcolor(7);
			printf(" Modificha delle impostazioni della rete in corso \n");
			system ("setting.bat");
			system ("NETSH WLAN start hostednetwork");	
			}	
		else
			{
			setcolor(4);
			printf(" Errore\nLa rete wifi non è stata configurata \n");
			setcolor(7);

			}
		}
	else
		{
		printf(" La rete wifi sta per essere avviata \n");
		system ("setting.bat");
		system ("NETSH WLAN start hostednetwork");	
		}
		
	fclose(set);		
	system ("PAUSE");	
	}
		

void stopwifi()
	{
	system("CLS");
	printf("       / Programma di Antonio Riccio 5H /\n");
	setcolor(4);
	printf("      //////////////////////////////////\n");
	setcolor(7);	
	printf("     /            Versione: %d         /\n",VERSIONE);
	setcolor(4);
	printf("    /________________________________/\n\n");
	setcolor(7);	
	printf(" La rete wifi sta per essere fermata\n ");
	setcolor(4);
	system ("NETSH WLAN stop hostednetwork");
	setcolor(7);
	system ("PAUSE");	
	}		


void statuswifi()
	{
	int s;
	char ssid[20];
	char key[20];	
	
	FILE *info;
	
	info=fopen ("info.txt","r");

	printf("       / Programma di Antonio Riccio 5H /\n");
	setcolor(3);	
	printf("      //////////////////////////////////\n");
	printf("     /             Wi-fi Status       /\n");
	setcolor(7);
	printf("    /            Versione: %d         /\n",VERSIONE);
	setcolor(3);	
	printf("   /________________________________/\n\n");
	setcolor(7);
		
	if (info==NULL)
		{
		printf("Non sono presenti file di configurazione\n");	
		printf("Vuoi crearli ora ?\n");
		setcolor(2);
		printf("1=YES ");	
		setcolor(4);
		printf("0=NO\n");
		setcolor(7);
		printf("Opzione: ");
		do
			{
			scanf("%d",&s);
			}
		while(s<0 || s>1);
		
		if (s==1)
			{
			settingwifi();
			}	
		}
	else
		{		
		fscanf(info,"%s",&ssid);
		fscanf(info,"%s",&key);
		
		
		printf ("SSID: %s \n", ssid);
		printf ("Password: %s \n\n", key);
		
		fclose(info);
	
		system("PAUSE");
		}
	}
	
void settingwifi()
	{
	int s;
	char ssid[20];
	char key[20];	
	
	FILE *set;
	FILE *info;
	
	printf("       / Programma di Antonio Riccio 5H /\n");
	setcolor(6);
	printf("      //////////////////////////////////\n");
	printf("     /             Wi-fi Setting      /\n");	
	setcolor(7);
	printf("    /            Versione: %d         /\n",VERSIONE);
	setcolor(6);
	printf("   /________________________________/\n");
	setcolor(7);
	

	
	cout << "\n\nNome della rete: ";
	cin >> ssid;	
	
	setcolor(6);
	cout << "\nLa password deve contenere almeno 8 caratteri ";
	setcolor(7);
	do 
		{
		cout << "\nPassword della rete: ";	
		cin >> key;
		}
	while (strlen(key)<8);
	
	set=fopen ("setting.bat","w");
	info=fopen ("info.txt","w");

	fprintf(info,"%s\n",ssid);
	fprintf(info,"%s\n",key);
	fprintf(set,"NETSH WLAN set hostednetwork mode=allow ssid=%s key=%s",ssid,key);

	fclose(info);
	fclose(set);
	
	system ("CLS");
	}
	