#include <stdafx.h>
#include <winsock2.h>
#include <Ws2bth.h>
#include <iostream>
#include <BluetoothAPIs.h>
#include <stdio.h>

using namespace std;

#pragma comment(lib, "ws2_32.lib")

#pragma comment(lib, "irprops.lib")

TCHAR *GetLastErrorMessage(DWORD last_error)
{
   static TCHAR errmsg[512];

   if (!FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, 
      0,
      last_error,
      0,
      errmsg, 
      511,
      NULL))
   {
      /* if we fail, call ourself to find out why and return that error */
      return (GetLastErrorMessage(GetLastError()));  
   }
  
   return errmsg;
}

BOOL __stdcall callback(
  ULONG uAttribId,
  LPBYTE pValueStream,
  ULONG cbStreamSize,
  LPVOID pvParam)
{
//   printf("Callback %d\n", uAttribId);

   SDP_ELEMENT_DATA element;

   if (ERROR_SUCCESS != BluetoothSdpGetElementData(pValueStream,  cbStreamSize, &element))
   {
       printf("%s\n", GetLastErrorMessage(GetLastError()));
   }


   return true;
}



int main(int argc, char* argv[])
{
   WORD wVersionRequested = 0x202;
   WSADATA m_data;
   BTH_ADDR tel_address;
   GUID tel_guid;


   if (0 == ::WSAStartup(wVersionRequested, &m_data))
   {
      SOCKET s = ::socket(AF_BTH, SOCK_STREAM, BTHPROTO_RFCOMM); 

      const DWORD lastError = ::GetLastError();

      if (s == INVALID_SOCKET)
      {
          printf("Failed to get bluetooth socket! %s\n", GetLastErrorMessage(lastError));
         exit(1);
      }

      WSAPROTOCOL_INFO protocolInfo;

      int protocolInfoSize = sizeof(protocolInfo);

      if (0 != getsockopt(s, SOL_SOCKET, SO_PROTOCOL_INFO, (char*)&protocolInfo, &protocolInfoSize))
      {
         exit(1);
      }

      
      WSAQUERYSET querySet;

      memset(&querySet, 0, sizeof(querySet));

      querySet.dwSize = sizeof(querySet);

      querySet.dwNameSpace = NS_BTH;

      HANDLE hLookup;
      DWORD flags = LUP_RETURN_NAME | LUP_CONTAINERS | LUP_RETURN_ADDR | LUP_FLUSHCACHE | LUP_RETURN_TYPE | LUP_RETURN_BLOB | LUP_RES_SERVICE;

      int result = WSALookupServiceBegin(&querySet, flags, &hLookup);
      int index = 0;
      if (0 == result)
      {
         while (0 == result)
         {
            BYTE buffer[1000];

            DWORD bufferLength = sizeof(buffer);

            WSAQUERYSET *pResults = (WSAQUERYSET*)&buffer;

            result = WSALookupServiceNext(hLookup, flags, &bufferLength, pResults);

            if (result == 0)
            {

               CSADDR_INFO *pCSAddr = (CSADDR_INFO *)pResults->lpcsaBuffer;

               BTH_DEVICE_INFO *pDeviceInfo = (BTH_DEVICE_INFO*)pResults->lpBlob;

               WSAQUERYSET querySet2;

               memset(&querySet2, 0, sizeof(querySet2));

               querySet2.dwSize = sizeof(querySet2);

               GUID protocol = L2CAP_PROTOCOL_UUID;

               querySet2.lpServiceClassId = &protocol;
   
               querySet2.dwNameSpace = NS_BTH;

               char addressAsString[1000];

               DWORD addressSize = sizeof(addressAsString);

               addressSize = sizeof(addressAsString);

               if (0 == WSAAddressToString(pCSAddr->RemoteAddr.lpSockaddr, pCSAddr->RemoteAddr.iSockaddrLength, &protocolInfo, addressAsString, &addressSize))
               {
                  printf("[%d] %s: %s\n", index, pResults->lpszServiceInstanceName, addressAsString);
                  if (index==4)
                  {
                    tel_address = pDeviceInfo->address;
                    tel_guid = protocol;
                  }
                  index++;
               }

            }
         }
         
         result = WSALookupServiceEnd(hLookup);
      }
      else
      {
         printf("%s\n", GetLastErrorMessage(GetLastError()));
      }
       SOCKET client_socket = socket (AF_BTH, SOCK_STREAM, BTHPROTO_RFCOMM);
       SOCKADDR_BTH sa;
       memset (&sa, 0, sizeof(sa));
       //sa.btAddr = tel_address;
       sa.addressFamily  = AF_BTH;
       sa.btAddr = 0x001EA3161152;
       GUID temp = {0x00080000, 0x0000, 0x1000, {0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB}};
       sa.serviceClassId = tel_guid;
       //sa.port = 0;
       if (connect (client_socket, (SOCKADDR *)&sa, sizeof(sa)))
       {
         cout << "err";
         cout << endl << WSAGetLastError();
         closesocket (client_socket);
       } else { cout << "ok"; closesocket (client_socket);}
      WSACleanup();
   }
   
   


  system("pause");
    return 0;
}
