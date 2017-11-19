#include <stdio.h>
#include <stdlib.h>

#include <winscard.h>

#define MAX_READER_NAME_SIZE 40

#ifndef MAX_ATR_SIZE
#define MAX_ATR_SIZE 33
#endif

int main(int argc, char **argv)
{
	SCARDCONTEXT hContext;
	SCARDHANDLE hCard;

	SCARD_READERSTATE_A rgReaderStates[1];

	DWORD dwReaderLen, dwState, dwProt, dwAtrLen;
	DWORD dwPref, dwReaders, dwRespLen;

	LPWSTR pcReaders;

	LPWSTR mszReaders;

	BYTE pbAtr[MAX_ATR_SIZE];

	BYTE pbResp1[30];
	BYTE pbResp2[30];
	BYTE pbResp3[30];
	BYTE pbResp4[30];
	BYTE pbResp5[200];

	LPCWSTR mszGroups;
	LONG rv;

	int i, p, iReader;
	int iReaders[16];

	//komendy


	//zarzadca
	printf("SCardEstablishContext : ");
	rv = SCardEstablishContext(SCARD_SCOPE_SYSTEM, NULL, NULL, &hContext);

	if (rv != SCARD_S_SUCCESS)
	{
		printf("failed\n");
		return -1;
	}
	else printf("success\n");

	// pobranie wielko¶ci ci±gu, jaki bêdzie potrzebny na listê 
	// dostêpnych czytników w systemie
	mszGroups = 0;
	printf("SCardListReaders : ");
	rv = SCardListReaders(hContext, mszGroups, 0, &dwReaders);

	if (rv != SCARD_S_SUCCESS)
	{
		SCardReleaseContext(hContext);
		printf("failed\n");
		return -1;
	}
	else printf("success\n");
	
	// alokacja pamiêci
	mszReaders = (LPWSTR)malloc(sizeof(char) * dwReaders);

	// pobranie listy czytników
	printf("SCardListReaders : ");
	rv = SCardListReaders(hContext, mszGroups, mszReaders, &dwReaders);

	if (rv != SCARD_S_SUCCESS)
	{
		SCardReleaseContext(hContext);
		free(mszReaders);
		printf("failed\n");
		return -1;
	}
	else printf("success\n");

	// wydruk listy znalezionych czytników
	p = 0;
	for (i = 0; i < dwReaders - 1; ++i)
	{
		iReaders[++p] = i;
		printf("Reader %02d: %s\n", p, &mszReaders[i]);
		// przesuniêcie bufora do kolejnej nazwy czytnika
		while (mszReaders[++i] != '\0');
	}

	do
	{
		printf("Select reader : ");
		scanf("%d", &iReader);
	} while (iReader > p || iReader <= 0);
	

	//iReader = 1;
	// nawi±zanie po³±czenia z czytnikiem
	printf("SCardConnect : ");
	rv = SCardConnect(hContext, &mszReaders[iReaders[iReader]],
		SCARD_SHARE_SHARED, SCARD_PROTOCOL_T0 | SCARD_PROTOCOL_T1,
		&hCard, &dwPref);

	if (rv != SCARD_S_SUCCESS)
	{
		SCardReleaseContext(hContext);
		free(mszReaders);
		printf("failed\n");
		return -1;
	}
	else printf("success\n");

	// sprawdzenie stanu karty w czytniku
	printf("SCardStatus : ");
	dwReaderLen = MAX_READER_NAME_SIZE;
	pcReaders = (LPWSTR)malloc(sizeof(char) * MAX_READER_NAME_SIZE);

	rv = SCardStatus(hCard, pcReaders, &dwReaderLen, &dwState,
		&dwProt, pbAtr, &dwAtrLen);

	if (rv != SCARD_S_SUCCESS)
	{
		SCardDisconnect(hCard, SCARD_RESET_CARD);
		SCardReleaseContext(hContext);
		free(mszReaders);
		free(pcReaders);
		printf("failed\n");
		return -1;
	}
	else printf("success\n");

	// wydruk pobranych informacji
	printf("Reader name : %s\n", pcReaders);
	printf("Reader state : %lx\n", dwState);
	printf("Reader protocol : %lx\n", dwProt - 1);
	printf("Reader ATR size : %d\n", dwAtrLen);
	printf("Reader ATR value : ");
		
	// wydruk ATR
	for (i = 0; i < dwAtrLen; i++)
	{
		printf("%02X ", pbAtr[i]);
	}
	printf("\n");
	//free(pcReaders);
	
	// rozpoczêcie transakcji z kart±
	printf("SCardBeginTransaction : ");
	rv = SCardBeginTransaction(hCard);
	if (rv != SCARD_S_SUCCESS)
	{
		SCardDisconnect(hCard, SCARD_RESET_CARD);
		SCardReleaseContext(hContext);
		printf("failed\n");
		free(mszReaders);
		return -1;
	}
	else printf("success\n");


	BYTE SELECT_TELECOM[] = { 0xA0, 0xA4, 0x00, 0x00, 0x02, 0x7F, 0x10 };
	// przes³anie do karty komendy 
	printf("SCardTransmit : ");
	dwRespLen = 30;
	rv = SCardTransmit(hCard, SCARD_PCI_T0, SELECT_TELECOM,
		7, NULL, pbResp1, &dwRespLen);

	if (rv != SCARD_S_SUCCESS)
	{
		SCardDisconnect(hCard, SCARD_RESET_CARD);
		SCardReleaseContext(hContext);
		printf("failed\n");
		free(mszReaders);
		return -1;
	}
	else printf("success\n");
	printf("Response APDU : ");

	// wydruk odpowiedzi karty
	for (i = 0; i < dwRespLen; i++)
	{
		printf("%02X ", pbResp1[i]);
	}
	printf("\n");


	BYTE GET_RESPONSE[] = { 0xA0, 0xC0, 0x00, 0x00, 0x1A};
	// przes³anie do karty komendy 
	printf("SCardTransmit : ");
	dwRespLen = 30;
	rv = SCardTransmit(hCard, SCARD_PCI_T0, GET_RESPONSE,
		5, NULL, pbResp2, &dwRespLen);

	if (rv != SCARD_S_SUCCESS)
	{
		SCardDisconnect(hCard, SCARD_RESET_CARD);
		SCardReleaseContext(hContext);
		printf("failed\n");
		free(mszReaders);
		return -1;
	}
	else printf("success\n");
	printf("Response APDU : ");

	// wydruk odpowiedzi karty
	for (i = 0; i < dwRespLen; i++)
	{
		printf("%02X ", pbResp2[i]);
	}
	printf("\n");

	BYTE SELECT_SMS[] = { 0xA0, 0xA4, 0x00, 0x00, 0x02, 0x6F, 0x3C };
	// przes³anie do karty komendy 
	printf("SCardTransmit : ");
	dwRespLen = 30;
	rv = SCardTransmit(hCard, SCARD_PCI_T0, SELECT_SMS,
		7, NULL, pbResp3, &dwRespLen);

	if (rv != SCARD_S_SUCCESS)
	{
		SCardDisconnect(hCard, SCARD_RESET_CARD);
		SCardReleaseContext(hContext);
		printf("failed\n");
		free(mszReaders);
		return -1;
	}
	else printf("success\n");
	printf("Response APDU : ");

	// wydruk odpowiedzi karty
	for (i = 0; i < dwRespLen; i++)
	{
		printf("%02X ", pbResp3[i]);
	}
	printf("\n");


	BYTE GET_RESPONSE2[] = { 0xA0, 0xC0, 0x00, 0x00, 0x0F };
	// przes³anie do karty komendy 
	printf("SCardTransmit : ");
	dwRespLen = 30;
	rv = SCardTransmit(hCard, SCARD_PCI_T0, GET_RESPONSE2,
		5, NULL, pbResp4, &dwRespLen);

	if (rv != SCARD_S_SUCCESS)
	{
		SCardDisconnect(hCard, SCARD_RESET_CARD);
		SCardReleaseContext(hContext);
		printf("failed\n");
		free(mszReaders);
		return -1;
	}
	else printf("success\n");
	printf("Response APDU : ");

	// wydruk odpowiedzi karty
	for (i = 0; i < dwRespLen; i++)
	{
		printf("%02X ", pbResp4[i]);
	}
	printf("\n");

	
	//for (int i = 1; i < 4; i++)
	//{
		BYTE READ_RECORD[] = { 0xA0, 0xB2, 0x01, 0x04, 0xB0 };
		// przes³anie do karty komendy 
		printf("SCardTransmit : ");
		dwRespLen = 178;
		rv = SCardTransmit(hCard, SCARD_PCI_T0, READ_RECORD,
			5, NULL, pbResp5, &dwRespLen);

		if (rv != SCARD_S_SUCCESS)
		{
			SCardDisconnect(hCard, SCARD_RESET_CARD);
			SCardReleaseContext(hContext);
			printf("failed\n");
			free(mszReaders);
			return -1;
		}
		else printf("success\n");
		printf("\nSMS1\nResponse APDU : ");

		// wydruk odpowiedzi karty
		for (i = 0; i < dwRespLen; i++)
		{
			printf("%02X ", pbResp5[i]);
		}
		printf("\n");
		//-----------------------------------
		BYTE READ_RECORD2[] = { 0xA0, 0xB2, 0x02, 0x04, 0xB0 };
		// przes³anie do karty komendy 
		printf("SCardTransmit : ");
		dwRespLen = 178;
		rv = SCardTransmit(hCard, SCARD_PCI_T0, READ_RECORD2,
			5, NULL, pbResp5, &dwRespLen);

		if (rv != SCARD_S_SUCCESS)
		{
			SCardDisconnect(hCard, SCARD_RESET_CARD);
			SCardReleaseContext(hContext);
			printf("failed\n");
			free(mszReaders);
			return -1;
		}
		else printf("success\n");
		printf("\nSMS2\nResponse APDU : ");

		// wydruk odpowiedzi karty
		for (i = 0; i < dwRespLen; i++)
		{
			printf("%02X ", pbResp5[i]);
		}
		printf("\n");

		/******************/

		BYTE READ_RECORD3[] = { 0xA0, 0xB2, 0x03, 0x04, 0xB0 };
		// przes³anie do karty komendy 
		printf("SCardTransmit : ");
		dwRespLen = 178;
		rv = SCardTransmit(hCard, SCARD_PCI_T0, READ_RECORD3,
			5, NULL, pbResp5, &dwRespLen);

		if (rv != SCARD_S_SUCCESS)
		{
			SCardDisconnect(hCard, SCARD_RESET_CARD);
			SCardReleaseContext(hContext);
			printf("failed\n");
			free(mszReaders);
			return -1;
		}
		else printf("success\n");
		printf("\nSMS3\nResponse APDU : ");

		// wydruk odpowiedzi karty
		for (i = 0; i < dwRespLen; i++)
		{
			printf("%02X ", pbResp5[i]);
		}
		printf("\n");
	//}

		/**********************/

		BYTE READ_RECORD4[] = { 0xA0, 0xB2, 0x04, 0x04, 0xB0 };
		// przes³anie do karty komendy 
		printf("SCardTransmit : ");
		dwRespLen = 178;
		rv = SCardTransmit(hCard, SCARD_PCI_T0, READ_RECORD2,
			5, NULL, pbResp5, &dwRespLen);

		if (rv != SCARD_S_SUCCESS)
		{
			SCardDisconnect(hCard, SCARD_RESET_CARD);
			SCardReleaseContext(hContext);
			printf("failed\n");
			free(mszReaders);
			return -1;
		}
		else printf("success\n");
		printf("\nSMS4\nResponse APDU : ");

		// wydruk odpowiedzi karty
		for (i = 0; i < dwRespLen; i++)
		{
			printf("%02X ", pbResp5[i]);
		}
		printf("\n");
	// zakoñczenie transakcji z kart±
	printf("SCardEndTransaction : ");
	rv = SCardEndTransaction(hCard, SCARD_LEAVE_CARD);
	if (rv != SCARD_S_SUCCESS)
	{
		SCardDisconnect(hCard, SCARD_RESET_CARD);
		SCardReleaseContext(hContext);
		printf("failed\n");
		free(mszReaders);
		return -1;
	}
	else printf("success\n");

	// od³±czenie od czytnika
	printf("SCardDisconnect : ");
	rv = SCardDisconnect(hCard, SCARD_UNPOWER_CARD);

	if (rv != SCARD_S_SUCCESS)
	{
		SCardReleaseContext(hContext);
		printf("failed\n");
		free(mszReaders);
		return -1;
	}
	else printf("success\n");

	// od³±czenie od zarz±dcy zasobów PC/SC
	printf("SCardReleaseContext : ");
	rv = SCardReleaseContext(hContext);

	if (rv != SCARD_S_SUCCESS)
	{
		printf("failed\n");
		free(mszReaders);
		return -1;
	}
	else printf("success\n");

	//free(mszReaders);
	return 0;
}