#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#include <Winsock2.h>
#include <initguid.h>
#include <roapi.h>
#include <windows.data.xml.dom.h>
#include <windows.data.json.h>
#include <Windows.h>
#include <Shlwapi.h>
#include <tlhelp32.h>
#include <Shlobj.h>
#include "resource.h"
#define INCLUDE_DEFAULTLIB
#undef INCLUDE_DEFAULTLIB
#ifdef INCLUDE_DEFAULTLIB
#include <stdio.h>
#define printf(...) if (fCon) { fprintf((fCon), __VA_ARGS__); fflush(fCon); }
#define wprintf(...) if (fCon) { fwprintf((fCon), __VA_ARGS__); fflush(fCon); }
#define __wcslen wcslen
#define __strlen strlen
#define __memset memset
#define __memcpy memcpy
#define __wcschr wcschr
#define __wcsstr wcsstr
FILE* fCon;
#else
#pragma comment(linker, "/NODEFAULTLIB")
#pragma comment(linker, "/ENTRY:wWinMain")
void printf(char* b, ...) {}
void wprintf(wchar_t* b, ...) {}
UINT32 __strlen(char* s)
{
    UINT32 k = 0;
    while (s[k])
    {
        k++;
    }
    return k;
}
#pragma optimize( "", off )
// https://hero.handmade.network/forums/code-discussion/t/94-guide_-_how_to_avoid_c_c++_runtime_on_windows
void* __memset(void* dest, int c, size_t count)
{
    char* bytes = (char*)dest;
    while (count--)
    {
        *bytes++ = (char)c;
    }
    return dest;
}
// https://hero.handmade.network/forums/code-discussion/t/94-guide_-_how_to_avoid_c_c++_runtime_on_windows
void* __memcpy(void* dest, const void* src, size_t count)
{
    char* dest8 = (char*)dest;
    const char* src8 = (const char*)src;
    while (count--)
    {
        *dest8++ = *src8++;
    }
    return dest;
}
#pragma optimize( "", on )
// https://android.googlesource.com/platform/bionic/+/ics-mr1-release/libc/wchar/wcslen.c
size_t __wcslen(const wchar_t* s)
{
    const wchar_t* p;
    p = s;
    while (*p)
        p++;
    return p - s;
}
// https://android.googlesource.com/platform/bionic/+/ics-mr1-release/libc/wchar/wcschr.c
wchar_t* __wcschr(const wchar_t* s, wchar_t c)
{
    while (*s != c && *s != L'\0')
        s++;
    if (*s == c)
        return ((wchar_t*)s);
    return (NULL);
}
// https://android.googlesource.com/platform/bionic/+/ics-mr1-release/libc/wchar/wcsncmp.c
int __wcsncmp(const wchar_t* s1, const wchar_t* s2, size_t n)
{
    if (n == 0)
        return (0);
    do {
        if (*s1 != *s2++) {
            /* XXX assumes wchar_t = int */
            return (*(const unsigned int*)s1 -
                *(const unsigned int*)--s2);
        }
        if (*s1++ == 0)
            break;
    } while (--n != 0);
    return (0);
}
// https://android.googlesource.com/platform/bionic/+/ics-mr1-release/libc/wchar/wcsstr.c
wchar_t* __wcsstr(const wchar_t* __restrict s, const wchar_t* __restrict find)
{
    wchar_t c, sc;
    size_t len;
    if ((c = *find++) != L'\0') {
        len = __wcslen(find);
        do {
            do {
                if ((sc = *s++) == L'\0')
                    return (NULL);
            } while (sc != c);
        } while (__wcsncmp(s, find, len) != 0);
        s--;
    }
    return ((wchar_t*)s);
}
#endif

// This is the AppUserModelId of an application from the Start menu
// If you don't supply a valid entry here, the toast will have no icon
// The ID below is for Mozilla Thunderbird
#define APP_ID L"D78BF5DD33499EC2"

// UUID obtained from <windows.ui.notifications.h>
//
// ABI.Windows.UI.Notifications.IToastNotificationManagerStatics
// 50ac103f-d235-4598-bbef-98fe4d1a3ad4
DEFINE_GUID(UIID_IToastNotificationManagerStatics,
    0x50ac103f,
    0xd235, 0x4598, 0xbb, 0xef,
    0x98, 0xfe, 0x4d, 0x1a, 0x3a, 0xd4
);

// UUID obtained from <windows.ui.notifications.h>
//
// ABI.Windows.Notifications.IToastNotificationFactory
// 04124b20-82c6-4229-b109-fd9ed4662b53
DEFINE_GUID(UIID_IToastNotificationFactory,
    0x04124b20,
    0x82c6, 0x4229, 0xb1, 0x09,
    0xfd, 0x9e, 0xd4, 0x66, 0x2b, 0x53
);

// UUID obtained from <windows.data.xml.dom.h>
//
// ABI.Windows.Data.Xml.Dom.IXmlDocument
// f7f3a506-1e87-42d6-bcfb-b8c809fa5494
DEFINE_GUID(UIID_IXmlDocument,
    0xf7f3a506,
    0x1e87, 0x42d6, 0xbc, 0xfb,
    0xb8, 0xc8, 0x09, 0xfa, 0x54, 0x94
);

// UUID obtained from <windows.data.xml.dom.h>
//
// ABI.Windows.Data.Xml.Dom.IXmlDocumentIO
// 6cd0e74e-ee65-4489-9ebf-ca43e87ba637
DEFINE_GUID(UIID_IXmlDocumentIO,
    0x6cd0e74e,
    0xee65, 0x4489, 0x9e, 0xbf,
    0xca, 0x43, 0xe8, 0x7b, 0xa6, 0x37
);

// UUID obtained from <windows.data.json.h>
//
// ABI.Windows.Data.Json.IJsonObjectStatics
// 2289f159-54de-45d8-abcc-22603fa066a0
DEFINE_GUID(UIID_IJsonObjectStatics,
    0x2289f159,
    0x54de, 0x45d8, 0xab, 0xcc,
    0x22, 0x60, 0x3f, 0xa0, 0x66, 0xa0
);

wchar_t xmlString[] =
L"<toast displayTimestamp=\"%\" scenario=\"%\" "
L"activationType=\"protocol\" launch=\"%\" duration=\"%\">\r\n"
L"	<visual>\r\n"
L"		<binding template=\"ToastGeneric\">\r\n"
L"			<text><![CDATA[%]]></text>\r\n"
L"			<text><![CDATA[%]]></text>\r\n"
L"			<text placement=\"attribution\"><![CDATA[%]]></text>\r\n"
L"		</binding>\r\n"
L"	</visual>\r\n"
L"	<audio src=\"%\" loop=\"%\" silent=\"%\"/>\r\n  %\r\n"
L"</toast>\r\n";

wchar_t* tokens[] = {
    L"id",
    L"date", 
    L"scenario", 
    L"launch", 
    L"duration", 
    L"subject", 
    L"body", 
    L"attr", 
    L"audio", 
    L"loop", 
    L"silent", 
    L"extra"
};
#define XML_TOKENS                         sizeof(tokens) / sizeof(tokens[0])

#define XML_MAX_SIZE                                                    10000
#define APPID_MAX_SIZE                                                   1000

#define TCP_BUFSIZ                                                       4096
#define TCP_PORT                                                        46578
#define _MAX_CMDLINE                                                     2048

#define TIMEOUT_RETRY_SOCKET 1000
#define TIMEOUT_EXEC_PROCESS                                            10000
#define TIMEOUT_REST                                                     2000
#define TIMEOUT_WINDOW_CHECK                                              100
#define TIMEOUT_FOREGROUND_CHECK                                            2
#define THUNDERBIRD_TITLE_PATTERN                   L" - Mozilla Thunderbird"

#define APP_NAME                                          L"ThunderbirdToasts"
#define PROTOCOL_NAME                                      "thunderbirdtoasts"
#define MANIFEST_NAME                                           L"native.json"
#define ADDON_NAME                              "ThunderbirdToasts@valinet.ro"
#define ADDON_NAME_WITH_EXTENSION                           ADDON_NAME L".xpi"
#define EXE_NAME                                     L"thunderbird_toasts.exe"

char* pszMsg = "HTTP/1.1 200 OK\r\n"
"Content-Type: text/html\r\n"
"Pragma: no-cache\r\n"
"Access-Control-Allow-Origin: *\r\n" // VERY IMPORTANT
"\r\n";

char installationFinished[] = "{\r\n"
"\"id\": \"D78BF5DD33499EC2\",\r\n"
"\"date\": \"\",\r\n"
"\"scenario\": \"reminder\",\r\n"
"\"launch\": \"" PROTOCOL_NAME "://0\",\r\n"
"\"duration\": \"long\",\r\n"
"\"subject\": \"Installation complete\",\r\n"
"\"body\": \"To enable the extension, go to Tools - "
"Add-ons, find it in the list and turn its switch on. To adjust the "
"configuration, click the [...] button and then Options.\",\r\n"
"\"attr\":\" \",\r\n"
"\"loop\": \"false\",\r\n"
"\"audio\": \"ms-winsoundevent:Notification.Default\",\r\n"
"\"silent\": \"false\",\r\n"
"\"extra\": \"<actions><action content=\\\"Dismiss\\\" arguments=\\\"\\\" "
"activationType=\\\"foreground\\\" /></actions>\"\r\n"
"}";

char unInstallationFinished[] = "{\r\n"
"\"id\": \"D78BF5DD33499EC2\",\r\n"
"\"date\": \"\",\r\n"
"\"scenario\": \"\",\r\n"
"\"launch\": \"http://valinet.ro/\",\r\n"
"\"duration\": \"long\",\r\n"
"\"subject\": \"Uninstall complete\",\r\n"
"\"body\": \"Do not forget to enable Thunderbird's built-in notification "
"feature. To learn more about other applications from us, click or touch here.\",\r\n"
"\"attr\":\" \",\r\n"
"\"loop\": \"false\",\r\n"
"\"audio\": \"ms-winsoundevent:Notification.Default\",\r\n"
"\"silent\": \"false\",\r\n"
"\"extra\": \"\"\r\n"
"}";

char nativeJson[] = "{\r\n"
"    \"name\": \"ThunderbirdToasts\",\r\n"
"    \"description\" : \"Native Windows 10 notification support for incoming mail.\",\r\n"
"    \"type\" : \"stdio\",\r\n"
"    \"allowed_extensions\" : [\"" ADDON_NAME "\"],\r\n"
"    \"path\": \"";

#define ERROR_FILE_COPY 4000
#define ERROR_SETTING_REGISTRY 4002
#define ERROR_TOAST 4003

DWORD WINAPI KillThread(
    _In_ LPVOID lpParameter
)
{
    Sleep(lpParameter);
    TerminateProcess(
        GetCurrentProcess(),
        0
    );
    return TRUE;
}

char* unescapeJSON(char* pszMessage, DWORD* dwszMessage)
{
    // TODO: Compute new correct size of message in dwszMessage
    char* buf1 = pszMessage;
    char* buf2 = pszMessage;
    for (UINT32 i = 0; i < *dwszMessage; i++)
    {
        if (*buf2 != '\\')
        {
            *buf1 = *buf2;
            buf1++;
        }
        else if (*buf2 == '\\' && *(buf2 + 1) == '\\')
        {
            *buf1 = '\\';
            buf1++;
            buf2 = buf2 + 1;
        }
        buf2++;
        if (*buf2 == '}')
        {
            *buf1 = '}';
            break;
        }
    }
    *(buf1 + 1) = 0;
    return pszMessage + sizeof(char);
}

HRESULT ShowToastMessage(
    __x_ABI_CWindows_CData_CXml_CDom_CIXmlDocument* inputXml,
    wchar_t* appId
)
{
    HRESULT hr = S_OK;

    HSTRING_HEADER header_AppIdHString;
    HSTRING AppIdHString;
    hr = WindowsCreateStringReference(
        appId,
        (UINT32)__wcslen(appId),
        &header_AppIdHString,
        &AppIdHString
    );
    if (FAILED(hr))
    {
        printf("%s:%d:: WindowsCreateStringReference\n", __FUNCTION__, __LINE__);
        goto exit1;
    }
    if (AppIdHString == NULL)
    {
        hr = E_POINTER;
        goto exit1;
    }

    HSTRING_HEADER header_ToastNotificationManagerHString;
    HSTRING ToastNotificationManagerHString;
    hr = WindowsCreateStringReference(
        RuntimeClass_Windows_UI_Notifications_ToastNotificationManager,
        (UINT32)__wcslen(RuntimeClass_Windows_UI_Notifications_ToastNotificationManager),
        &header_ToastNotificationManagerHString,
        &ToastNotificationManagerHString
    );
    if (FAILED(hr))
    {
        printf("%s:%d:: WindowsCreateStringReference\n", __FUNCTION__, __LINE__);
        goto exit2;
    }
    if (ToastNotificationManagerHString == NULL)
    {
        printf("%s:%d:: ToastNotificationManagerHString == NULL\n", __FUNCTION__, __LINE__);
        hr = E_POINTER;
        goto exit2;
    }

    __x_ABI_CWindows_CUI_CNotifications_CIToastNotificationManagerStatics* toastStatics = NULL;
    hr = RoGetActivationFactory(
        ToastNotificationManagerHString,
        &UIID_IToastNotificationManagerStatics,
        (LPVOID*)&toastStatics
    );
    if (FAILED(hr))
    {
        printf("%s:%d:: RoGetActivationFactory\n", __FUNCTION__, __LINE__);
        goto exit2;
    }

    __x_ABI_CWindows_CUI_CNotifications_CIToastNotifier* notifier;
    hr = toastStatics->lpVtbl->CreateToastNotifierWithId(
        toastStatics,
        AppIdHString,
        &notifier
    );
    if (FAILED(hr))
    {
        printf("%s:%d:: CreateToastNotifierWithId\n", __FUNCTION__, __LINE__);
        goto exit3;
    }

    HSTRING_HEADER header_ToastNotificationHString;
    HSTRING ToastNotificationHString;
    hr = WindowsCreateStringReference(
        RuntimeClass_Windows_UI_Notifications_ToastNotification,
        (UINT32)__wcslen(RuntimeClass_Windows_UI_Notifications_ToastNotification),
        &header_ToastNotificationHString,
        &ToastNotificationHString
    );
    if (FAILED(hr))
    {
        printf("%s:%d:: WindowsCreateStringReference\n", __FUNCTION__, __LINE__);
        goto exit4;
    }
    if (ToastNotificationHString == NULL)
    {
        printf("%s:%d:: ToastNotificationHString == NULL\n", __FUNCTION__, __LINE__);
        hr = E_POINTER;
        goto exit4;
    }

    __x_ABI_CWindows_CUI_CNotifications_CIToastNotificationFactory* notifFactory = NULL;
    hr = RoGetActivationFactory(
        ToastNotificationHString,
        &UIID_IToastNotificationFactory,
        (LPVOID*)&notifFactory
    );
    if (FAILED(hr))
    {
        printf("%s:%d:: RoGetActivationFactory\n", __FUNCTION__, __LINE__);
        goto exit4;
    }

    __x_ABI_CWindows_CUI_CNotifications_CIToastNotification* toast = NULL;
    hr = notifFactory->lpVtbl->CreateToastNotification(notifFactory, inputXml, &toast);
    if (FAILED(hr))
    {
        printf("%s:%d:: CreateToastNotification\n", __FUNCTION__, __LINE__);
        goto exit5;
    }

    hr = notifier->lpVtbl->Show(notifier, toast);
    if (FAILED(hr))
    {
        printf("%s:%d:: Show\n", __FUNCTION__, __LINE__);
        goto exit6;
    }

exit6:
    toast->lpVtbl->Release(toast);
exit5:
    notifFactory->lpVtbl->Release(notifFactory);
exit4:
    notifier->lpVtbl->Release(notifier);
exit3:
    toastStatics->lpVtbl->Release(toastStatics);
exit2:
    inputXml->lpVtbl->Release(inputXml);
exit1:
exit0:
    return hr;
}

HRESULT PopulateToastMessage(
    char* pszData,
    DWORD dwLength,
    wchar_t* appIdBuffer,
    __x_ABI_CWindows_CData_CXml_CDom_CIXmlDocument** pxmlToastMessage
)
{
    HRESULT hr = S_OK;

    wchar_t* pwszData;
    if (!(pwszData = VirtualAlloc(
        NULL,
        dwLength * sizeof(wchar_t),
        MEM_RESERVE | MEM_COMMIT,
        PAGE_READWRITE
    )))
    {
        printf(
            "%s:%d:: VirtualAlloc = %d\n", __FUNCTION__, __LINE__,
            GetLastError()
        );
        hr = GetLastError();
        goto exit0;
    }

    if (!MultiByteToWideChar(
        CP_UTF8,
        MB_PRECOMPOSED,
        pszData,
        dwLength,
        pwszData,
        dwLength
    ))
    {
        hr = GetLastError();
        goto exit1;
    }

    HSTRING_HEADER hshjsonData_h;
    HSTRING hsjsonData;
    hr = WindowsCreateStringReference(
        pwszData,
        (UINT32)__wcslen(pwszData),
        &hshjsonData_h,
        &hsjsonData
    );
    if (FAILED(hr))
    {
        printf(
            "%s:%d:: WindowsCreateStringReference = %d\n", __FUNCTION__, __LINE__,
            hr
        );
        goto exit1;
    }
    if (hsjsonData == NULL)
    {
        printf("%s:%d:: hsjsonData == NULL\n", __FUNCTION__, __LINE__);
        hr = E_POINTER;
        goto exit1;
    }

    HSTRING_HEADER hshJsonObjectS_h;
    HSTRING hsJsonObjectS;
    hr = WindowsCreateStringReference(
        RuntimeClass_Windows_Data_Json_JsonObject,
        (UINT32)__wcslen(RuntimeClass_Windows_Data_Json_JsonObject),
        &hshJsonObjectS_h,
        &hsJsonObjectS
    );
    if (FAILED(hr))
    {
        printf(
            "%s:%d:: WindowsCreateStringReference = %d\n", __FUNCTION__, __LINE__,
            hr
        );
        goto exit1;
    }
    if (hsJsonObjectS == NULL)
    {
        printf("%s:%d:: hJsonObjectS == NULL\n", __FUNCTION__, __LINE__);
        hr = E_POINTER;
        goto exit1;
    }

    HSTRING_HEADER hshXmlDocumentS_h;
    HSTRING hsXmlDocumentS;
    hr = WindowsCreateStringReference(
        RuntimeClass_Windows_Data_Xml_Dom_XmlDocument,
        (UINT32)__wcslen(RuntimeClass_Windows_Data_Xml_Dom_XmlDocument),
        &hshXmlDocumentS_h,
        &hsXmlDocumentS
    );
    if (FAILED(hr))
    {
        printf(
            "%s:%d:: WindowsCreateStringReference = %d\n", __FUNCTION__, __LINE__,
            hr
        );
        goto exit1;
    }
    if (hsXmlDocumentS == NULL)
    {
        printf("%s:%d:: hJsonObjectS == NULL\n", __FUNCTION__, __LINE__);
        hr = E_POINTER;
        goto exit1;
    }

    __x_ABI_CWindows_CData_CJson_CIJsonObjectStatics* pJsonObjectClass = NULL;
    hr = RoGetActivationFactory(
        hsJsonObjectS,
        &UIID_IJsonObjectStatics,
        (LPVOID*)&pJsonObjectClass
    );
    if (FAILED(hr))
    {
        printf(
            "%s:%d:: RoGetActivationFactory = %d\n", __FUNCTION__, __LINE__,
            hr
        );
        goto exit1;
    }

    __x_ABI_CWindows_CData_CJson_CIJsonObject* pjsonObject = NULL;
    hr = pJsonObjectClass->lpVtbl->Parse(
        pJsonObjectClass,
        hsjsonData,
        &pjsonObject
    );
    if (FAILED(hr))
    {
        printf(
            "%s:%d:: pJsonObjectClass.Parse = %d\n", __FUNCTION__, __LINE__,
            hr
        );
        goto exit2;
    }

    IInspectable* pInspectable = NULL;
    hr = RoActivateInstance(hsXmlDocumentS, &pInspectable);
    if (SUCCEEDED(hr))
    {
        hr = pInspectable->lpVtbl->QueryInterface(
            pInspectable,
            &UIID_IXmlDocument,
            pxmlToastMessage
        );
        pInspectable->lpVtbl->Release(pInspectable);
    }
    else
    {
        printf(
            "%s:%d:: RoActivateInstance = %d\n", __FUNCTION__, __LINE__,
            hr
        );
        goto exit3;
    }

    __x_ABI_CWindows_CData_CXml_CDom_CIXmlDocumentIO* pxmlDocumentIO = NULL;
    (*pxmlToastMessage)->lpVtbl->QueryInterface(
        (*pxmlToastMessage),
        &UIID_IXmlDocumentIO,
        &pxmlDocumentIO
    );
    if (FAILED(hr))
    {
        printf(
            "%s:%d:: QueryInterface = %d\n", __FUNCTION__, __LINE__,
            hr
        );
        goto exit3;
    }

    wchar_t* pwszBuffer = NULL;
    if (!(pwszBuffer = VirtualAlloc(
        NULL,
        XML_MAX_SIZE * sizeof(wchar_t),
        MEM_RESERVE | MEM_COMMIT,
        PAGE_READWRITE
    )))
    {
        printf(
            "%s:%d:: VirtualAlloc = %d\n", __FUNCTION__, __LINE__,
            GetLastError()
        );
        hr = GetLastError();
        goto exit4;
    }

    wchar_t* pwszBufferCurrent = pwszBuffer;
    wchar_t* pwszCurrent = xmlString;
    for (UINT32 i = 0; i < XML_TOKENS; ++i)
    {
        if (!(tokens[i][0] == 'i' && tokens[i][1] == 'd'))
        {
            wchar_t* pszFin = __wcschr(pwszCurrent, '%');
            __memcpy(
                pwszBufferCurrent,
                pwszCurrent,
                (pszFin - pwszCurrent) * sizeof(wchar_t)
            );
            pwszBufferCurrent = pwszBufferCurrent + (pszFin - pwszCurrent);
            pwszCurrent = pszFin + 1;
        }

        HSTRING_HEADER hshToken_h;
        HSTRING hsToken;
        hr = WindowsCreateStringReference(
            tokens[i],
            (UINT32)__wcslen(tokens[i]),
            &hshToken_h,
            &hsToken
        );
        if (FAILED(hr))
        {
            printf(
                "%s:%d:: WindowsCreateStringReference = %d\n", __FUNCTION__, __LINE__,
                hr
            );
            continue;
        }
        if (hsToken == NULL)
        {
            printf("%s:%d:: hJsonObjectS == NULL\n", __FUNCTION__, __LINE__);
            hr = E_POINTER;
            continue;
        }

        HSTRING valueHString;
        pjsonObject->lpVtbl->GetNamedString(
            pjsonObject,
            hsToken,
            &valueHString
        );
        if (FAILED(hr))
        {
            printf(
                "%s:%d:: pjsonObject->GetNamedString = %d\n", __FUNCTION__, __LINE__,
                hr
            );
            continue;
        }

        UINT32 length;
        wchar_t* raw = WindowsGetStringRawBuffer(
            valueHString,
            &length
        );
        if (!(tokens[i][0] == 'i' && tokens[i][1] == 'd'))
        {
            __memcpy(
                pwszBufferCurrent,
                raw,
                length * sizeof(wchar_t)
            );
            pwszBufferCurrent = pwszBufferCurrent + length;
        }
        else
        {
            __memcpy(
                appIdBuffer,
                raw,
                length * sizeof(wchar_t)
            );
        }
    }

    wchar_t* pszFin = __wcschr(pwszCurrent, 0);
    __memcpy(
        pwszBufferCurrent,
        pwszCurrent,
        (pszFin - pwszCurrent) * sizeof(wchar_t)
    );

    wprintf(
        L"%s:%d:: XML =\n%s\n", __FUNCTION__, __LINE__,
        pwszBuffer
    );

    HSTRING_HEADER hshxmlString_h;
    HSTRING hshxmlString;
    hr = WindowsCreateStringReference(
        pwszBuffer,
        (UINT32)__wcslen(pwszBuffer),
        &hshxmlString_h,
        &hshxmlString
    );
    if (FAILED(hr))
    {
        printf(
            "%s:%d:: WindowsCreateStringReference = %d\n", __FUNCTION__, __LINE__,
            hr
        );
        goto exit5;
    }
    if (hshxmlString == NULL)
    {
        printf("%s:%d:: hJsonObjectS == NULL\n", __FUNCTION__, __LINE__);
        hr = E_POINTER;
        goto exit5;
    }

    hr = pxmlDocumentIO->lpVtbl->LoadXml(pxmlDocumentIO, hshxmlString);
    if (FAILED(hr))
    {
        printf(
            "%s:%d:: pxmlDocumentIO->LoadXml = %d\n", __FUNCTION__, __LINE__,
            hr
        );
        goto exit5;
    }
exit5:
    VirtualFree(
        pwszBuffer,
        0,
        MEM_RELEASE
    );
exit4:
    pxmlDocumentIO->lpVtbl->Release(pxmlDocumentIO);
exit3:
    pjsonObject->lpVtbl->Release(pjsonObject);
exit2:
    pJsonObjectClass->lpVtbl->Release(pJsonObjectClass);
exit1:
    VirtualFree(
        pwszData,
        0,
        MEM_RELEASE
    );
exit0:
    return hr;
}

HRESULT OnNativeMessage(
    HANDLE hFile
)
{
    HRESULT hr;
    DWORD dwNumberOfBytesRead = 0;
    DWORD32 dwszMessage = 0;
    CHAR* pszMessage;

    hr = RoInitialize(RO_INIT_MULTITHREADED);
    if (FAILED(hr))
    {
        return hr;
    }

    printf("%s:%d:: Begin\n", __FUNCTION__, __LINE__);

    while (TRUE)
    {
        if (ReadFile(
            hFile,
            &dwszMessage,
            4,
            &dwNumberOfBytesRead,
            NULL
        ) == TRUE && dwNumberOfBytesRead == 4)
        {
            printf(
                "%s:%d:: dwNumberOfBytesRead = %d\n", __FUNCTION__, __LINE__,
                dwNumberOfBytesRead
            );

            if (!(pszMessage = VirtualAlloc(
                NULL,
                dwszMessage,
                MEM_RESERVE | MEM_COMMIT,
                PAGE_READWRITE
            )))
            {
                printf(
                    "%s:%d:: VirtualAlloc = %d\n", __FUNCTION__, __LINE__,
                    GetLastError()
                );
                goto endOnNativeMessage;
            }

            if (ReadFile(
                hFile,
                pszMessage,
                dwszMessage,
                &dwNumberOfBytesRead,
                NULL
            ) == TRUE && dwNumberOfBytesRead == dwszMessage)
            {
                char* pszMessageNew = unescapeJSON(pszMessage, &dwszMessage);
                printf(
                    "%s:%d:: Unescaped pszMessage = %s\n", __FUNCTION__, __LINE__,
                    pszMessageNew
                );

                wchar_t* appIdBuffer = NULL;
                if (!(appIdBuffer = VirtualAlloc(
                    NULL,
                    APPID_MAX_SIZE * sizeof(wchar_t),
                    MEM_RESERVE | MEM_COMMIT,
                    PAGE_READWRITE
                )))
                {
                    printf(
                        "%s:%d:: VirtualAlloc = %d\n", __FUNCTION__, __LINE__,
                        GetLastError()
                    );
                    hr = GetLastError();
                    goto endOnNativeMessage;
                }
                __x_ABI_CWindows_CData_CXml_CDom_CIXmlDocument* inputXml = NULL;
                hr = PopulateToastMessage(
                    pszMessageNew,
                    dwszMessage,
                    appIdBuffer,
                    &inputXml
                );
                if (FAILED(hr))
                {
                    printf(
                        "%s:%d:: PopulateToastMessage\n", __FUNCTION__, __LINE__
                    );
                    continue;
                }
                hr = ShowToastMessage(
                    inputXml,
                    appIdBuffer
                );
                if (FAILED(hr))
                {
                    printf(
                        "%s:%d:: ShowToastMessage\n", __FUNCTION__, __LINE__
                    );
                    continue;
                }
                if (!VirtualFree(
                    appIdBuffer,
                    0,
                    MEM_RELEASE
                ))
                {
                    printf(
                        "%s:%d:: VirtualFree = %d\n", __FUNCTION__, __LINE__,
                        GetLastError()
                    );
                    goto endOnNativeMessage;
                }
            }
            else
            {
                printf(
                    "%s:%d:: ReadFile = %d\n", __FUNCTION__, __LINE__,
                    GetLastError()
                );
                if (!VirtualFree(
                    pszMessage,
                    0,
                    MEM_RELEASE
                ))
                {
                    printf(
                        "%s:%d:: VirtualFree = %d\n", __FUNCTION__, __LINE__,
                        GetLastError()
                    );
                    goto endOnNativeMessage;
                }
                return TRUE;
            }
            if (!VirtualFree(
                pszMessage,
                0,
                MEM_RELEASE
            ))
            {
                printf(
                    "%s:%d:: VirtualFree = %d\n", __FUNCTION__, __LINE__,
                    GetLastError()
                );
                goto endOnNativeMessage;
            }
        }
        else
        {
            printf(
                "%s:%d:: ReadFile = %d\n", __FUNCTION__, __LINE__,
                GetLastError()
            );
            goto endOnNativeMessage;
        }
    }

    RoUninitialize();

    return hr;

endOnNativeMessage:
    TerminateProcess(
        GetCurrentProcess(),
        0
    );
}

void SendNativeMessage(HANDLE hFile, char* pszData)
{
    DWORD dwNumberOfBytesWritten = 0;
    DWORD32 dwszData;
    dwszData = (DWORD32)__strlen(pszData);
    if (!WriteFile(
        hFile,
        &dwszData,
        4,
        &dwNumberOfBytesWritten,
        NULL
    ) || dwNumberOfBytesWritten != 4)
    {
        printf(
            "%s:%d:: WriteFile = %d\n", __FUNCTION__, __LINE__,
            GetLastError()
        );
        return;
    }
    if (!WriteFile(
        hFile,
        pszData,
        dwszData,
        &dwNumberOfBytesWritten,
        NULL
    ) || dwNumberOfBytesWritten != dwszData)
    {
        printf(
            "%s:%d:: WriteFile = %d\n", __FUNCTION__, __LINE__,
            GetLastError()
        );
        return;
    }
    if (!FlushFileBuffers(hFile))
    {
        printf(
            "%s:%d:: FlushFileBuffers = %d\n", __FUNCTION__, __LINE__,
            GetLastError()
        );
        return;
    }
}

//http://stackoverflow.com/questions/210504/enumerate-windows-like-alt-tab-does
BOOL IsAltTabWindow(HWND hwnd)
{
    HWND hwndWalk = GetAncestor(hwnd, GA_ROOTOWNER);

    HWND hwndTry;
    while ((hwndTry = GetLastActivePopup(hwndWalk)) != hwndTry) {
        if (IsWindowVisible(hwndTry)) break;
        hwndWalk = hwndTry;
    }
    return hwndWalk == hwnd;
}

BOOL CALLBACK EnumWindowsProc(
    HWND hWnd,
    LPARAM lParam
) {
    wchar_t* buff;
    if (!(buff = VirtualAlloc(
        NULL,
        TCP_BUFSIZ * sizeof(wchar_t),
        MEM_RESERVE | MEM_COMMIT,
        PAGE_READWRITE
    )))
    {
        printf(
            "%s:%d:: VirtualAlloc = %d\n", __FUNCTION__, __LINE__,
            GetLastError()
        );
        return TRUE;
    }

    if (IsAltTabWindow(hWnd)) {
        GetWindowText(hWnd, (LPSTR)buff, TCP_BUFSIZ - 1);
        if (__wcsstr(buff, THUNDERBIRD_TITLE_PATTERN))
        {
            DWORD dwPid;
            GetWindowThreadProcessId(hWnd, &dwPid);
            if (dwPid == *((HWND*)lParam))
            {
                *((HWND*)lParam) = hWnd;
                VirtualFree(
                    buff,
                    0,
                    MEM_RELEASE
                );
                return FALSE;
            }
        }
    }

    VirtualFree(
        buff,
        0,
        MEM_RELEASE
    );
    return TRUE;
}

DWORD start_thunderbird()
{
    HWND hWnd = NULL;
    HANDLE hThread = NULL;
    BOOL bResult = FALSE;
    HMODULE hUser32 = GetModuleHandle(L"User32");
    if (hUser32 == NULL)
    {
        return GetLastError();
    }
    FARPROC hAdrSetForegroundWindow = GetProcAddress(
        hUser32,
        "SetForegroundWindow"
    );
    PROCESSENTRY32 entry;
    entry.dwSize = sizeof(PROCESSENTRY32);
    HANDLE snapshot = NULL;
    HANDLE hProcess = NULL;
    STARTUPINFO stSI;
    PROCESS_INFORMATION stPI;
    HANDLE key;
    TCHAR* psztbPath;
    DWORD sztbPath = _MAX_CMDLINE;
    if (!(psztbPath = VirtualAlloc(
        NULL,
        _MAX_CMDLINE * sizeof(wchar_t),
        MEM_RESERVE | MEM_COMMIT,
        PAGE_READWRITE
    )))
    {
        printf(
            "%s:%d:: VirtualAlloc = %d\n", __FUNCTION__, __LINE__,
            GetLastError()
        );
        return GetLastError();
    }
    DWORD dwType = REG_SZ;
    DWORD dwProcessIdThunderbird = 0;
    DWORD dwProcessIdExplorer = 0;
    DWORD dwProcessIdWinlogon = 0;

    if (!CreateThread(
        NULL,
        NULL,
        KillThread,
        TIMEOUT_EXEC_PROCESS,
        NULL,
        NULL
    ))
    {
        return GetLastError();
    }
    if (RegOpenKeyEx(
        HKEY_LOCAL_MACHINE,
        L"SOFTWARE\\Clients\\Mail\\Mozilla Thunderbird\\shell\\open\\command",
        0,
        KEY_READ,
        &key
    ) != ERROR_SUCCESS)
    {
        return 0;
    }
    if (RegQueryValueEx(
        key,
        NULL,
        NULL,
        &dwType,
        psztbPath,
        &sztbPath
    ) != ERROR_SUCCESS)
    {
        RegCloseKey(key);
        return 0;
    }
    RegCloseKey(key);
    PathRemoveArgs(psztbPath);
    ZeroMemory(
        &stSI,
        sizeof(stSI)
    );
    stSI.cb = sizeof(stSI);
    ZeroMemory(
        &stPI,
        sizeof(stPI)
    );
    snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
    /*if (Process32First(snapshot, &entry) == TRUE)
    {
        while (Process32Next(snapshot, &entry) == TRUE)
        {
            if (!wcscmp(entry.szExeFile, L"winlogon.exe"))
            {
                dwProcessIdWinlogon = entry.th32ProcessID;
                break;
            }
        }
    }*/
    if (Process32First(snapshot, &entry) == TRUE)
    {
        while (Process32Next(snapshot, &entry) == TRUE)
        {
            if (!wcscmp(entry.szExeFile, L"thunderbird.exe")
                && !dwProcessIdThunderbird
                )
            {
                dwProcessIdThunderbird = entry.th32ProcessID;
            }
            else if (!wcscmp(entry.szExeFile, L"explorer.exe")
                && !dwProcessIdExplorer
                //&& entry.th32ParentProcessID == dwProcessIdWinlogon
                )
            {
                dwProcessIdExplorer = entry.th32ProcessID;
            }
            if (dwProcessIdThunderbird && dwProcessIdExplorer)
            {
                break;
            }
        }
    }
    if (!CloseHandle(snapshot))
    {
        return GetLastError();
    }
    if (!dwProcessIdExplorer)
    {
        return 0;
    }
    if (!CreateProcess(
        NULL,
        psztbPath,
        NULL,
        NULL,
        FALSE,
        0,
        NULL,
        NULL,
        &stSI,
        &stPI
    ))
    {
        return GetLastError();
    }
    if (!dwProcessIdThunderbird)
    {
        dwProcessIdThunderbird = stPI.dwProcessId;
    }
    if (!CloseHandle(stPI.hProcess))
    {
        return GetLastError();
    }
    if (!CloseHandle(stPI.hThread))
    {
        return GetLastError();
    }
    while (TRUE)
    {
        hWnd = dwProcessIdThunderbird;
        EnumWindows(
            EnumWindowsProc,
            &hWnd
        );
        if (hWnd != dwProcessIdThunderbird)
        {
            break;
        }
        Sleep(TIMEOUT_WINDOW_CHECK);
    }
    ShowWindow(
        hWnd,
        SW_SHOW
    );
    if (hProcess = OpenProcess(
        PROCESS_ALL_ACCESS,
        FALSE,
        dwProcessIdExplorer
    ))
    {
        if (!(hThread = CreateRemoteThread(
            hProcess,
            NULL,
            0,
            (LPTHREAD_START_ROUTINE)hAdrSetForegroundWindow,
            hWnd,
            CREATE_SUSPENDED,
            NULL
        )))
        {
            return GetLastError();
        }
        if (ResumeThread(
            hThread
        ) == (DWORD)-1)
        {
            return GetLastError();
        }
        if (WaitForSingleObject(
            hThread,
            INFINITE
        ) != WAIT_OBJECT_0)
        {
            return GetLastError();
        }
        if (!CloseHandle(hProcess))
        {
            return GetLastError();
        }
    }
    else
    {
        return GetLastError();
    }
    /*while (GetForegroundWindow() != hWnd)
    {
        Sleep(TIMEOUT_FOREGROUND_CHECK);
    }
    keybd_event(VK_LCONTROL, 0, 0, 0);
    keybd_event(VK_LSHIFT, 0, 0, 0);
    keybd_event(VkKeyScan('q'), 0, 0, 0);
    keybd_event(VkKeyScan('q'), 0, KEYEVENTF_KEYUP, 0);
    keybd_event(VK_LSHIFT, 0, KEYEVENTF_KEYUP, 0);
    keybd_event(VK_LCONTROL, 0, KEYEVENTF_KEYUP, 0);
    */


    VirtualFree(
        psztbPath,
        0,
        MEM_RELEASE
    );
    return 0;
}

DWORD post_message()
{
    WSADATA stWsa;
    SOCKET hSock;
    struct sockaddr_in stCln;

    if (WSAStartup(
        MAKEWORD(2, 2), 
        &stWsa
    ))
    {
        return GetLastError();
    }

    if ((hSock = socket(
        AF_INET, 
        SOCK_STREAM, 
        0
    )) == INVALID_SOCKET)
    {
        return GetLastError();
    }

    stCln.sin_addr.s_addr = inet_addr("127.0.0.1");
    stCln.sin_family = AF_INET;
    stCln.sin_port = htons(TCP_PORT);

    //Connect to remote server
    if (connect(
        hSock, 
        (struct sockaddr*)&stCln, 
        sizeof(stCln)
    ) < 0)
    {
        ExitProcess(0);
    }

    if (send(
        hSock,
        PathGetArgsA(GetCommandLineA()),
        strlen(PathGetArgsA(GetCommandLineA())),
        0
    ) == SOCKET_ERROR)
    {
        return GetLastError();
    }

    if (closesocket(hSock) == SOCKET_ERROR)
    {
        return GetLastError();
    }

    if (WSACleanup() == SOCKET_ERROR)
    {
        return GetLastError();
    }

    return 0;
}

BOOL GetWorkingDirectory(wchar_t* directory)
{
    /*
    TCHAR szAppName[_MAX_PATH];
    GetModuleFileName(
        GetModuleHandle(NULL),
        szAppName,
        _MAX_PATH
    );
    PathStripPath(
        szAppName
    );
    */
    wchar_t* szAppName = EXE_NAME;
    BOOL bRet = TRUE;
    HRESULT hr = SHGetFolderPath(
        NULL,
        CSIDL_APPDATA,
        NULL,
        SHGFP_TYPE_CURRENT,
        directory
    );
    if (SUCCEEDED(hr))
    {
        __memcpy(
            directory + __wcslen(directory),
            L"\\ThunderbirdToasts",
            (18 + 1) * sizeof(wchar_t)
        );
        bRet = CreateDirectory(
            directory,
            NULL
        );
        if (bRet || (bRet == 0 && GetLastError() == ERROR_ALREADY_EXISTS))
        {
            __memcpy(
                directory + __wcslen(directory),
                L"\\",
                (1 + 1) * sizeof(wchar_t)
            );
            __memcpy(
                directory + __wcslen(directory),
                szAppName,
                (__wcslen(szAppName) + 1) * sizeof(wchar_t)
            );
        }
    }
    else
    {
        bRet = FALSE;
    }
    return bRet;
}

BOOL UnpackFileToDisk(
    int name,
    int type,
    char* filename
)
{
    HRSRC hRscr = FindResource(
        GetModuleHandle(NULL), 
        name,
        type
    );
    if (hRscr) {
        HGLOBAL hgRscr = LoadResource(
            GetModuleHandle(NULL), 
            hRscr
        );
        if (hgRscr) {
            PVOID pRscr = LockResource(hgRscr);
            DWORD cbRscr = SizeofResource(
                GetModuleHandle(NULL), 
                hRscr
            );
            HANDLE hFile = CreateFile(
                filename, 
                GENERIC_WRITE,
                0, 
                NULL, 
                CREATE_ALWAYS,
                FILE_ATTRIBUTE_NORMAL,
                NULL
            );
            if (hFile)
            {
                DWORD dwNumberOfBytesWritten = 0;
                if (WriteFile(
                    hFile,
                    pRscr,
                    cbRscr,
                    &dwNumberOfBytesWritten,
                    NULL
                ))
                {
                    CloseHandle(hFile);
                    return TRUE;
                }
            }
        }
    }
    return FALSE;
}

BOOL install(BOOL uninstall)
{
    HRESULT hr;
    DWORD dwLen;
    TCHAR szCommandName[_MAX_PATH];
    TCHAR szAppName[_MAX_PATH];
    TCHAR szManifest[_MAX_PATH];
    TCHAR szExtension[_MAX_PATH];

    GetModuleFileName(
        GetModuleHandle(NULL),
        szAppName,
        _MAX_PATH
    );
    GetWorkingDirectory(szCommandName);
    if (!uninstall)
    {
        if (!CopyFile(
            szAppName,
            szCommandName,
            FALSE
        ))
        {
            return ERROR_FILE_COPY;
        }
    }
    GetWorkingDirectory(szAppName);
    PathStripPath(
        szAppName
    );
    GetWorkingDirectory(szManifest);
    PathRemoveFileSpec(szManifest);
    __memcpy(
        szManifest + __wcslen(szManifest),
        L"\\"
        MANIFEST_NAME,
        (1 + __wcslen(MANIFEST_NAME) + 1) * sizeof(wchar_t)
    );
    GetWorkingDirectory(szExtension);
    PathRemoveFileSpec(szExtension);
    __memcpy(
        szExtension + __wcslen(szExtension),
        L"\\"
        TEXT(ADDON_NAME_WITH_EXTENSION),
        (1 + __wcslen(TEXT(ADDON_NAME_WITH_EXTENSION)) + 1) * sizeof(wchar_t)
    );

    PROCESSENTRY32 entry;
    entry.dwSize = sizeof(PROCESSENTRY32);
    HANDLE snapshot = NULL;
    HANDLE hProcess = NULL;
    snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
    if (Process32First(snapshot, &entry) == TRUE)
    {
        while (Process32Next(snapshot, &entry) == TRUE)
        {
            if (!wcscmp(entry.szExeFile, L"thunderbird.exe"))
            {
                if (hProcess = OpenProcess(
                    PROCESS_ALL_ACCESS,
                    FALSE,
                    entry.th32ProcessID
                ))
                {
                    TerminateProcess(
                        hProcess,
                        0
                    );
                    CloseHandle(hProcess);
                }
            }
        }
    }
    if (!CloseHandle(snapshot))
    {
        return GetLastError();
    }
    Sleep(500);

    if (!uninstall)
    {
        HANDLE hFile = CreateFile(
            szManifest,
            GENERIC_WRITE,
            0,
            NULL,
            CREATE_ALWAYS,
            FILE_ATTRIBUTE_NORMAL,
            NULL
        );
        if (!hFile)
        {
            return ERROR_FILE_COPY;
        }
        DWORD dwNumberOfBytesWritten = 0;
        if (!WriteFile(
            hFile,
            nativeJson,
            __strlen(nativeJson),
            &dwNumberOfBytesWritten,
            NULL
        ))
        {
            return ERROR_FILE_COPY;
        }
        char commandName[_MAX_PATH];
        __memset(
            commandName,
            0,
            _MAX_PATH
        );
        WideCharToMultiByte(
            CP_UTF8,
            NULL,
            szCommandName,
            __wcslen(szCommandName),
            commandName,
            _MAX_PATH,
            NULL,
            NULL
        );
        char* escapedCommandLine = (char*)szCommandName;
        for (size_t i = 0; i < __strlen(commandName); i++)
        {
            escapedCommandLine[0] = commandName[i];
            if (commandName[i] == '\\')
            {
                escapedCommandLine++;
                escapedCommandLine[0] = '\\';
            }
            escapedCommandLine++;
        }
        escapedCommandLine[0] = 0;
        escapedCommandLine = (char*)szCommandName;
        if (!WriteFile(
            hFile,
            escapedCommandLine,
            __strlen(escapedCommandLine),
            &dwNumberOfBytesWritten,
            NULL
        ))
        {
            return ERROR_FILE_COPY;
        }
        if (!WriteFile(
            hFile,
            "\"\r\n}",
            4 * sizeof(char),
            &dwNumberOfBytesWritten,
            NULL
        ))
        {
            return ERROR_FILE_COPY;
        }
        CloseHandle(hFile);
        if (!UnpackFileToDisk(
            MAKEINTRESOURCE(IDR_EXTENSION),
            MAKEINTRESOURCE(EXTENSION),
            szExtension
        ))
        {
            return ERROR_FILE_COPY;
        }
    }

    GetWorkingDirectory(szCommandName + 1);
    dwLen = __wcslen(szCommandName);
    szCommandName[0] = '"';
    szCommandName[dwLen] = '"';
    szCommandName[dwLen + 1] = ' ';
    szCommandName[dwLen + 2] = '%';
    szCommandName[dwLen + 3] = '1';
    szCommandName[dwLen + 4] = 0;

    HKEY root = HKEY_CURRENT_USER;
    /*
    if (IsUserAnAdmin())
    {
        root = HKEY_CLASSES_ROOT;
    }
    */

    DWORD dwDisposition;
    DWORD dwVal = 2162688;
    HKEY key;
    if (!uninstall)
    {
        if (RegCreateKeyEx(
            root,
            L"SOFTWARE\\Classes\\"
            TEXT(PROTOCOL_NAME),
            0,
            NULL,
            REG_OPTION_NON_VOLATILE,
            KEY_ALL_ACCESS,
            NULL,
            &key,
            &dwDisposition
        ) != ERROR_SUCCESS)
        {
            return ERROR_SETTING_REGISTRY;
        }
        if (RegSetValueEx(
            key,
            L"",
            0,
            REG_SZ,
            L"URL:"
            TEXT(PROTOCOL_NAME)
            L" protocol",
            (4 + __wcslen(TEXT(PROTOCOL_NAME)) + 9) * sizeof(wchar_t)
        ) != ERROR_SUCCESS)
        {
            return ERROR_SETTING_REGISTRY;
        }
        if (RegSetValueEx(
            key,
            L"EditFlags",
            0,
            REG_DWORD,
            &dwVal,
            sizeof(DWORD)
        ) != ERROR_SUCCESS)
        {
            return ERROR_SETTING_REGISTRY;
        }
        if (RegSetValueEx(
            key,
            L"URL Protocol",
            0,
            REG_SZ,
            L"",
            sizeof(wchar_t)
        ) != ERROR_SUCCESS)
        {
            return ERROR_SETTING_REGISTRY;
        }
        RegCloseKey(key);

        if (RegCreateKeyEx(
            root,
            L"SOFTWARE\\Classes\\"
            TEXT(PROTOCOL_NAME)
            L"\\shell\\open\\command",
            0,
            NULL,
            REG_OPTION_NON_VOLATILE,
            KEY_ALL_ACCESS,
            NULL,
            &key,
            &dwDisposition
        ) != ERROR_SUCCESS)
        {
            return ERROR_SETTING_REGISTRY;
        }
        if (RegSetValueEx(
            key,
            L"",
            0,
            REG_SZ,
            szCommandName,
            (__wcslen(szCommandName) + 1) * sizeof(wchar_t)
        ) != ERROR_SUCCESS)
        {
            return ERROR_SETTING_REGISTRY;
        }
        RegCloseKey(key);
    }
    else
    {
        int n = SHDeleteKey(
            root,
            L"SOFTWARE\\Classes\\"
            TEXT(PROTOCOL_NAME)
        );
        if (n && n != 2)
        {
            return ERROR_SETTING_REGISTRY;
        }
    }

    if (!uninstall)
    {
        if (RegCreateKeyEx(
            root,
            L"Software\\Mozilla\\NativeMessagingHosts\\"
            APP_NAME,
            0,
            NULL,
            REG_OPTION_NON_VOLATILE,
            KEY_ALL_ACCESS,
            NULL,
            &key,
            &dwDisposition
        ) != ERROR_SUCCESS)
        {
            return ERROR_SETTING_REGISTRY;
        }
        if (RegSetValueEx(
            key,
            L"",
            0,
            REG_SZ,
            szManifest,
            (__wcslen(szManifest) + 1) * sizeof(wchar_t)
        ) != ERROR_SUCCESS)
        {
            return ERROR_SETTING_REGISTRY;
        }
        RegCloseKey(key);
    }
    else
    {
        int n = SHDeleteKey(
            root,
            L"Software\\Mozilla\\NativeMessagingHosts\\"
            APP_NAME
        );
        if (n && n != 2)
        {
            return ERROR_SETTING_REGISTRY;
        }
    }

    hr = SHGetFolderPath(
        NULL,
        CSIDL_APPDATA,
        NULL,
        SHGFP_TYPE_CURRENT,
        &szAppName
    );
    if (FAILED(hr))
    {
        return ERROR_SETTING_REGISTRY;
    }
    __memcpy(
        szAppName + __wcslen(szAppName),
        L"\\Thunderbird\\Profiles\\*",
        (23 + 1) * sizeof(wchar_t)
    );

    WIN32_FIND_DATA ffd;
    HANDLE hFind;
    if (!(hFind = FindFirstFile(
        szAppName,
        &ffd
    )) == INVALID_HANDLE_VALUE)
    {
        return GetLastError();
    }
    do
    {
        if ((ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
            && __wcsstr(ffd.cFileName, L"default-release"))
        {
            __memcpy(
                szAppName + __wcslen(szAppName) - 1,
                ffd.cFileName,
                (__wcslen(ffd.cFileName) + 1) * sizeof(wchar_t)
            );
            __memcpy(
                szAppName + __wcslen(szAppName),
                L"\\extensions\\",
                (12 + 1) * sizeof(wchar_t)
            );
            __memcpy(
                szAppName + __wcslen(szAppName),
                TEXT(ADDON_NAME_WITH_EXTENSION),
                (__wcslen(TEXT(ADDON_NAME_WITH_EXTENSION)) + 1) * sizeof(wchar_t)
            );
            break;
        }
    } while (FindNextFile(hFind, &ffd) != 0);
    FindClose(hFind);

    if (!uninstall)
    {
        if (!CopyFile(
            szExtension,
            szAppName,
            FALSE
        ))
        {
            return ERROR_FILE_COPY;
        }
    }
    else
    {
        if (!DeleteFile(szAppName))
        {
            return ERROR_FILE_COPY;
        }
    }

    hr = RoInitialize(RO_INIT_MULTITHREADED);
    if (FAILED(hr))
    {
        return hr;
    }
    wchar_t* xmlPatch = __wcsstr(xmlString, L"displayTimestamp");
    for (size_t i = 0; i < 20; ++i)
    {
        if (xmlPatch[i] != '%')
        {
            xmlPatch[i] = ' ';
        }
    }

    wchar_t* appIdBuffer = NULL;
    if (!(appIdBuffer = VirtualAlloc(
        NULL,
        APPID_MAX_SIZE * sizeof(wchar_t),
        MEM_RESERVE | MEM_COMMIT,
        PAGE_READWRITE
    )))
    {
        printf(
            "%s:%d:: VirtualAlloc = %d\n", __FUNCTION__, __LINE__,
            GetLastError()
        );
        hr = GetLastError();
        return ERROR_TOAST;
    }
    __x_ABI_CWindows_CData_CXml_CDom_CIXmlDocument* inputXml = NULL;
    hr = PopulateToastMessage(
        !uninstall ? installationFinished : unInstallationFinished,
        __strlen(!uninstall ? installationFinished : unInstallationFinished),
        appIdBuffer,
        &inputXml
    );
    if (FAILED(hr))
    {
        printf(
            "%s:%d:: PopulateToastMessage\n", __FUNCTION__, __LINE__
        );
        return ERROR_TOAST;
    }
    hr = ShowToastMessage(
        inputXml,
        appIdBuffer
    );
    if (FAILED(hr))
    {
        printf(
            "%s:%d:: ShowToastMessage\n", __FUNCTION__, __LINE__
        );
        return ERROR_TOAST;
    }
    if (!VirtualFree(
        appIdBuffer,
        0,
        MEM_RELEASE
    ))
    {
        printf(
            "%s:%d:: VirtualFree = %d\n", __FUNCTION__, __LINE__,
            GetLastError()
        );
        return ERROR_TOAST;
    }

    start_thunderbird();
    post_message();

    RoUninitialize();

    return TRUE;
}

DWORD KeepMinimized(
    HWND hWnd
)
{
    size_t i = 0;
    while (i < 5000)
    {
        if (!IsIconic(hWnd))
        {
            Sleep(100);
            ShowWindow(hWnd, SW_MINIMIZE);
            Sleep(5);
            ShowWindow(hWnd, SW_HIDE);
            return 0;
        }
        i += 10;
        Sleep(10);
    }
    return 0;
}

int WINAPI wWinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR lpCmdLine,
    _In_ int nShowCmd
)
{
#ifdef INCLUDE_DEFAULTLIB
    AllocConsole();
    fopen_s(&fCon, "CONOUT$", "w");
#endif

    SetProcessDpiAwarenessContext(
        DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2
    );

    size_t argc = 0;
    LocalFree(CommandLineToArgvW(GetCommandLine(), &argc));
    if (argc == 2)
    {
        argc = start_thunderbird();
        if (argc)
        {
            return argc;
        }
        return post_message();
    }

    
    BOOL bOtherInstance = FALSE;
    TCHAR szAppName[_MAX_PATH];
    GetModuleFileName(
        GetModuleHandle(NULL),
        szAppName,
        _MAX_PATH
    );
    PathStripPath(
        szAppName
    );

    DWORD dwProcessIdThunderbird = 0;
    HWND hWnd = NULL;
    PROCESSENTRY32 entry;
    entry.dwSize = sizeof(PROCESSENTRY32);
    HANDLE snapshot = NULL;
    HANDLE hProcess = NULL;
    snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
    if (Process32First(snapshot, &entry) == TRUE)
    {
        while (Process32Next(snapshot, &entry) == TRUE)
        {
            if (!wcscmp(entry.szExeFile, szAppName) 
                && entry.th32ProcessID != GetCurrentProcessId())
            {
                bOtherInstance = TRUE;
                /*if (hProcess = OpenProcess(
                    PROCESS_ALL_ACCESS,
                    FALSE,
                    entry.th32ProcessID
                ))
                {
                    TerminateProcess(
                        hProcess,
                        0
                    );
                    CloseHandle(hProcess);
                }*/
            }
            if (!wcscmp(entry.szExeFile, L"thunderbird.exe")
                && !dwProcessIdThunderbird
                )
            {
                dwProcessIdThunderbird = entry.th32ProcessID;
            }
        }
    }
    if (!CloseHandle(snapshot))
    {
        return GetLastError();
    }
    

    if (argc == 1)
    {
        // TO DO
        // regsiter protocol on HKCU
        // register native messaging on HKCU
        // copy extension to Thunderbird
        // open Thunderbird

        return install(bOtherInstance);
    }

    printf("%s:%d:: Begin\n", __FUNCTION__, __LINE__);
    HANDLE hOnNativeMessage = NULL;

    if (!(hOnNativeMessage = CreateThread(
        NULL,
        (SIZE_T)0,
        OnNativeMessage,
        GetStdHandle(STD_INPUT_HANDLE),
        (DWORD)0,
        NULL
    )))
    {
        printf(
            "%s:%d:: CreateThread = %d\n", __FUNCTION__, __LINE__,
            GetLastError()
        );
        return 0;
    }


    while (TRUE)
    {
        hWnd = dwProcessIdThunderbird;
        EnumWindows(
            EnumWindowsProc,
            &hWnd
        );
        if (hWnd != dwProcessIdThunderbird)
        {
            break;
        }
        Sleep(TIMEOUT_WINDOW_CHECK);
    }
    //printf("%d %d\n", hWnd, IsIconic(hWnd));
    if (IsIconic(hWnd))
    {
        CreateThread(
            NULL,
            (SIZE_T)0,
            KeepMinimized,
            hWnd,
            (DWORD)0,
            NULL
        );
    }




    WSADATA stWsa;
    SOCKET hSrvSock, hClnSock;
    struct sockaddr_in stSrv, stCln;
    int szSt_sockaddr_in;
    char* pszRcvBuf;
    szSt_sockaddr_in = sizeof(struct sockaddr_in);
    stSrv.sin_family = AF_INET;
    stSrv.sin_addr.s_addr = INADDR_LOOPBACK;
    stSrv.sin_port = htons(TCP_PORT);

    if (!(pszRcvBuf = VirtualAlloc(
        NULL,
        TCP_BUFSIZ * sizeof(char),
        MEM_RESERVE | MEM_COMMIT,
        PAGE_READWRITE
    )))
    {
        printf(
            "%s:%d:: VirtualAlloc = %d\n", __FUNCTION__, __LINE__,
            GetLastError()
        );
        return GetLastError();
    }

    while (TRUE)
    {
        if (WSAStartup(
            MAKEWORD(2, 2),
            &stWsa
        ))
        {
            Sleep(TIMEOUT_RETRY_SOCKET);
            continue;
        }
        if ((hSrvSock = socket(
            AF_INET,
            SOCK_STREAM,
            0
        )) == INVALID_SOCKET)
        {
            Sleep(TIMEOUT_RETRY_SOCKET);
            continue;
        }
        if (bind(
            hSrvSock,
            (struct sockaddr*)&stSrv,
            szSt_sockaddr_in
        ) == SOCKET_ERROR)
        {
            Sleep(TIMEOUT_RETRY_SOCKET);
            continue;
        }
        if (listen(
            hSrvSock,
            1
        ) == SOCKET_ERROR)
        {
            Sleep(TIMEOUT_RETRY_SOCKET);
            continue;
        }
        while (TRUE)
        {
            if ((hClnSock = accept(
                hSrvSock,
                (struct sockaddr*)&stCln,
                &szSt_sockaddr_in
            )) == INVALID_SOCKET)
            {
                Sleep(TIMEOUT_RETRY_SOCKET);
                break;
            }
            __memset(
                pszRcvBuf,
                0,
                TCP_BUFSIZ
            );
            pszRcvBuf[0] = '{';
            pszRcvBuf[1] = '"';
            pszRcvBuf[2] = 'm';
            pszRcvBuf[3] = '"';
            pszRcvBuf[4] = ':';
            pszRcvBuf[5] = ' ';
            pszRcvBuf[6] = '"';
            if (recv(
                hClnSock,
                pszRcvBuf + 7,
                TCP_BUFSIZ - 10,
                0
            ) == SOCKET_ERROR)
            {
                continue;
            }
            if ((pszRcvBuf[7] == 'G' 
                && pszRcvBuf[8] == 'E' 
                && pszRcvBuf[9] == 'T'
                ) || (
                pszRcvBuf[7] == 'P'
                && pszRcvBuf[8] == 'O'
                && pszRcvBuf[9] == 'S'
                && pszRcvBuf[10] == 'T'
                )
            )
            {
                if (send(
                    hClnSock,
                    pszMsg,
                    __strlen(pszMsg),
                    0
                ) == SOCKET_ERROR)
                {
                    continue;
                }
            }
            else if ((pszRcvBuf[7] == 'O'
                && pszRcvBuf[8] == 'P'
                && pszRcvBuf[9] == 'T'
                && pszRcvBuf[10] == 'I'
                && pszRcvBuf[11] == 'O'
                && pszRcvBuf[12] == 'N'
                && pszRcvBuf[13] == 'S'
            ))
            {
                if (send(
                    hClnSock,
                    pszMsg,
                    __strlen(pszMsg),
                    0
                ) == SOCKET_ERROR)
                {
                    continue;
                }
                TCHAR szAppName[_MAX_PATH];
                GetModuleFileName(
                    GetModuleHandle(NULL),
                    szAppName,
                    _MAX_PATH
                );
                STARTUPINFO stSI;
                PROCESS_INFORMATION stPI;
                ZeroMemory(
                    &stSI,
                    sizeof(stSI)
                );
                stSI.cb = sizeof(stSI);
                ZeroMemory(
                    &stPI,
                    sizeof(stPI)
                );
                if (!CreateProcess(
                    NULL,
                    szAppName,
                    NULL,
                    NULL,
                    FALSE,
                    CREATE_BREAKAWAY_FROM_JOB,
                    NULL,
                    NULL,
                    &stSI,
                    &stPI
                ))
                {
                    return GetLastError();
                }
                if (!CloseHandle(stPI.hProcess))
                {
                    return GetLastError();
                }
                if (!CloseHandle(stPI.hThread))
                {
                    return GetLastError();
                }
            }
            for (size_t i = 0; i < TCP_BUFSIZ; ++i)
            {
                if (!pszRcvBuf[i] || pszRcvBuf[i] == '\r')
                {
                    pszRcvBuf[i] = '"';
                    pszRcvBuf[i + 1] = '}';
                    pszRcvBuf[i + 2] = 0;
                    break;
                }
            }
            printf(
                "%s:%d:: SendNativeMessage = %s\n", __FUNCTION__, __LINE__,
                pszRcvBuf
            );
            SendNativeMessage(
                GetStdHandle(STD_OUTPUT_HANDLE),
                pszRcvBuf
            );
            if (closesocket(hClnSock) == SOCKET_ERROR)
            {
            }
        }
    }

	return 0;
}
