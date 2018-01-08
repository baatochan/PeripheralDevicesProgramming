
/*----------------------------------------------------------------------------------------------------*/

#include <iostream>

#include <winsock2.h>
#include <Ws2bth.h>
#include <BluetoothAPIs.h>

#include <stdio.h>

using namespace std;

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

      if (0 == result)
      {
         while (0 == result)
         {
            BYTE buffer[1000];

            DWORD bufferLength = sizeof(buffer);

            WSAQUERYSET *pResults = (WSAQUERYSET*)&buffer;

            result = WSALookupServiceNext(hLookup, flags, &bufferLength, pResults);

            if (result != 0)
            {
               printf("%s\n", GetLastErrorMessage(GetLastError()));
               printf("%d\n", bufferLength);
            }
            else
            {
               printf("%s\n", pResults->lpszServiceInstanceName);

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

               if (0 == WSAAddressToString(pCSAddr->LocalAddr.lpSockaddr, pCSAddr->LocalAddr.iSockaddrLength, &protocolInfo, addressAsString, &addressSize))
               {  
                  printf("local address: %s\n", addressAsString);
               }

               addressSize = sizeof(addressAsString);

               if (0 == WSAAddressToString(pCSAddr->RemoteAddr.lpSockaddr, pCSAddr->RemoteAddr.iSockaddrLength, &protocolInfo, addressAsString, &addressSize))
               {
                  printf("device address: %s\n", addressAsString);
               }




               querySet2.lpszContext = addressAsString;

               HANDLE hLookup2;
               DWORD flags = LUP_FLUSHCACHE |LUP_RETURN_NAME | LUP_RETURN_TYPE | LUP_RETURN_ADDR | LUP_RETURN_BLOB | LUP_RETURN_COMMENT;

               int result = WSALookupServiceBegin(&querySet2, flags, &hLookup2);

               if (0 == result)
               {
                  while (0 == result)
                  {
                     BYTE buffer[2000];

                     DWORD bufferLength = sizeof(buffer);

                     WSAQUERYSET *pResults = (WSAQUERYSET*)&buffer;

                     result = WSALookupServiceNext(hLookup2, flags, &bufferLength, pResults);

                     if (result != 0)
                     {
                        printf("%s\n", GetLastErrorMessage(GetLastError()));
                        printf("%d\n", bufferLength);
                     }
                     else
                     {
                        printf("%s\n", pResults->lpszServiceInstanceName);
                        //printf("%s\n", pResults->lpszComment);

                        CSADDR_INFO *pCSAddr = (CSADDR_INFO *)pResults->lpcsaBuffer;

                        addressSize = sizeof(addressAsString);

                        if (0 == WSAAddressToString(pCSAddr->LocalAddr.lpSockaddr, pCSAddr->LocalAddr.iSockaddrLength, &protocolInfo, addressAsString, &addressSize))
                        {  
                           printf("local address: %s\n", addressAsString);
                        }

                        addressSize = sizeof(addressAsString);

                        if (0 == WSAAddressToString(pCSAddr->RemoteAddr.lpSockaddr, pCSAddr->RemoteAddr.iSockaddrLength, &protocolInfo, addressAsString, &addressSize))
                        {
                           printf("device address: %s\n", addressAsString);
                        }

                        if (pResults->lpBlob)
                        {
                           const BLOB *pBlob = (BLOB*)pResults->lpBlob;

                           if (!BluetoothSdpEnumAttributes(pBlob->pBlobData, pBlob->cbSize, callback, 0))
                           {
                              printf("BluetoothSdpEnumAttributes - %s\n", GetLastErrorMessage(GetLastError()));
                           }

                        }

                     }
                  }
         
                  result = WSALookupServiceEnd(hLookup2);

               }
               else
               {
                  printf("%s\n", GetLastErrorMessage(GetLastError()));
               }

            }
         }
         
         result = WSALookupServiceEnd(hLookup);
      }
      else
      {
         printf("%s\n", GetLastErrorMessage(GetLastError()));
      }

      WSACleanup();
   }

   HANDLE hRadio;
   BLUETOOTH_FIND_RADIO_PARAMS btfrp = { sizeof(btfrp) };

   HBLUETOOTH_RADIO_FIND hFind = BluetoothFindFirstRadio( &btfrp, &hRadio );

   if ( NULL != hFind )
   {
      printf("hFind\n");

      do
      {
         //
         //  TODO: Do something with the radio handle.
         //

		 BLUETOOTH_RADIO_INFO radioInfo;

		 radioInfo.dwSize = sizeof(radioInfo);

		 if (ERROR_SUCCESS == BluetoothGetRadioInfo(hRadio, &radioInfo))
		 {
			wprintf(L"Raido: %s\n", radioInfo.szName);
		 }

		 BLUETOOTH_DEVICE_INFO_STRUCT deviceInfo;

		 deviceInfo.dwSize = sizeof(deviceInfo);

		 BLUETOOTH_DEVICE_SEARCH_PARAMS deviceSearchParams;

		 memset(&deviceSearchParams, 0, sizeof(deviceSearchParams));

		 deviceSearchParams.dwSize = sizeof(deviceSearchParams);

		 //deviceSearchParams.fReturnAuthenticated = true;
		 deviceSearchParams.fReturnRemembered = true;
		 //deviceSearchParams.fReturnUnknown = true;
		 //deviceSearchParams.fReturnConnected = true;

		 deviceSearchParams.hRadio = hRadio;

		 HANDLE hDeviceFind = BluetoothFindFirstDevice(&deviceSearchParams, &deviceInfo);

		 if (NULL != hDeviceFind)
		 {
			 do
			 {
				 wprintf(L"Device: %s\n", deviceInfo.szName);

				 //BluetoothDisplayDeviceProperties(0, &deviceInfo);
			 }
			 while(BluetoothFindNextDevice(hDeviceFind, &deviceInfo));

			 BluetoothFindDeviceClose(hDeviceFind);
		 }


		 if (BluetoothGetDeviceInfo(hRadio, &deviceInfo))
		 {
			wprintf(L"+ Device: %s\n", deviceInfo.szName);

			// BluetoothUpdateDeviceRecord - change name

			// BluetoothRemoveDevice

		 }

		 GUID guidServices[10];

		 DWORD numServices = sizeof(guidServices);

		 DWORD result = BluetoothEnumerateInstalledServices(hRadio, &deviceInfo, &numServices, guidServices);

		          CloseHandle( hRadio );
      } while( BluetoothFindNextRadio( hFind, &hRadio ) );

      BluetoothFindRadioClose( hFind );
   }
   int abc;
   cin >> abc;

	return 0;
}