// Program.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


#include "stdlib.h"
#include "stdio.h"
#include <iostream>
#include <fstream>
#include "C:\Advantech\DAQNavi\Inc\bdaqctrl.h"
#include "C:\Advantech\DAQNavi\Inc\compatibility.h"
#include <Windows.h>
using namespace Automation::BDaq;

#define device L"USB-4702,BID#0"
int32 sChannel = 4; // kanal
const int32 channelAmount = 1, samplesPS = 64 /*probki/sec*/, samplingT = 100 /*sec*/, sampleC = samplesPS * samplingT;

#define USER_BUFFER_SIZE channelAmount * sampleC
double Y[USER_BUFFER_SIZE]; // kontener na otput


inline void waitAnyKey()
{
	do
	{
		SLEEP(1);
	} while (!kbhit());
}

class StoppedHandler : public BfdAiEventListener
{
public:
	virtual void BDAQCALL BfdAiEvent(void * sender, BfdAiEventArgs * args)
	{
		BufferedAiCtrl* bufferedAiCtrl = (BufferedAiCtrl*)sender;
		bufferedAiCtrl->GetData(args->Count, Y);
		int startChan = bufferedAiCtrl->getScanChannel()->getChannelStart();
		int chanCount = bufferedAiCtrl->getScanChannel()->getChannelCount();
		int channelCountMax = bufferedAiCtrl->getFeatures()->getChannelCountMax();

		printf("Pierwsza probka dla kazdego kanalu:\n\n");
		for (int32 i = 0; i < chanCount; ++i)
		{
			printf("KANAL %d: %10.6f \n", (i + startChan) % channelCountMax, Y[i]);
		}
		printf("\n\n");
	}
};

int main(int argc, char* argv[])
{
	ErrorCode ret = Success;
	// stworzenie bufferedaictrl dla kontroli nad buforowano funkcja AI
	BufferedAiCtrl * bfdAiCtrl = AdxBufferedAiCtrlCreate();
	// ustaw powiadomienia z handlera zdarzen bysmy mogli widziec stan zdarzenia efektywniej
	StoppedHandler onStopped;
	bfdAiCtrl->addStoppedListener(onStopped);

	do
	{
		// wybranie urzadzenia przez jego numer i opis, ustawienie trybu dostepu, uzywamy AccessWriteWithReset(default) by miec pelna kontrole nad urzadzeniem
		DeviceInformation devInfo(device);
		ret = bfdAiCtrl->setSelectedDevice(devInfo);
		CHK_RESULT(ret);
		ret = bfdAiCtrl->setStreaming(false); // ustaw tryb uruchomieniowy: one-buffered.
		CHK_RESULT(ret);

		ScanChannel* scanChannel = bfdAiCtrl->getScanChannel();
		ret = scanChannel->setChannelStart(sChannel);
		CHK_RESULT(ret);
		ret = scanChannel->setChannelCount(channelAmount);
		CHK_RESULT(ret);
		ret = scanChannel->setSamples(sampleC);
		CHK_RESULT(ret);

		// przygotuj bufor
		ret = bfdAiCtrl->Prepare();
		CHK_RESULT(ret);

		// rozpocznij asynchroniczne odczytywanie sygnalu
		printf("Asynchroniczna akwizycja w TRAKCIE!\n");
		printf("CZEKAJ, SPOKOJNIE... ZAJETY JESTEM... NACISNIJ COS BY ZAKONCZYC!\n\n");
		ret = bfdAiCtrl->Start();
		CHK_RESULT(ret);

		// kiedy urzadzenie pobiera dane - rob co chcesz
		do
		{
			//SLEEP(1);
			SLEEP(samplingT);
		} while (!kbhit());

		ret = bfdAiCtrl->Stop();
		CHK_RESULT(ret);
	} while (false);

	// zamknij 
	bfdAiCtrl->Dispose();

	std::ofstream samplesFile;
	samplesFile.open("samples.txt");
	for (int i = 0; i < USER_BUFFER_SIZE; i++)
	{
		// std::cout << Y[i] << std::endl;
		samplesFile << Y[i] << std::endl;
	}
	samplesFile.close();

	// obsluga bledu
	if (BioFailed(ret))
	{
		printf("Some error occurred. And the last error code is Ox%X.\n", ret);
		waitAnyKey();
	}

	return 0;
}





