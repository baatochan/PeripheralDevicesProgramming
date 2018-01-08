#pragma once

#include <list>
#include <winsock2.h>
#include <BluetoothAPIs.h>
#include <ws2bth.h>
#include <iostream>
#include <string>
#include <fstream>



//#include <obex.h>

//Magiczna Liczba. Dla niej dzia³a. Nie ruszaaaaac
#define MAX_PACKET_SIZE 127
//#define PRINT_INFO
//Nie wiêcej.

class Bluetooth
{
    static std::list<HANDLE*> available_adapters;
    BLUETOOTH_FIND_RADIO_PARAMS bt_find_radio_params;
    HANDLE* selected_adapter;
    static std::list<BLUETOOTH_DEVICE_INFO*> devices;
	
public:
    BLUETOOTH_DEVICE_INFO* selected_device;
	static short uploadStatus;
public:
    Bluetooth(void);
    ~Bluetooth(void);
    static void show_adapter_details(HANDLE*, bool details = false);
    static void show_device_details(BLUETOOTH_DEVICE_INFO*, bool details = false);
    int FindAdapters(bool refresh = true); //Returns how many adapters has been found.
    int Look_For_Devices(bool refresh = true); //Returns how many adapters has been found.
    void select_device(int);
    bool authenticate_selected_device();
    bool send_file(std::string data);
    
};
