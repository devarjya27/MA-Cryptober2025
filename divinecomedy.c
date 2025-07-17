#include <stdio.h>
#include <windows.h>
#include <shlobj.h> //provides declaration for shell object functions, used for accessing user/system folders.
#include <time.h>
#include <initguid.h> // Required to define custom GUIDs
#include <shellapi.h> // For ShellExecute and other shell-related functions

// Define the GUID for the Desktop folder used with SHGetKnownFolderPath ()
const GUID FOLDERID_Desktop = { 0xB4BFCC3A, 0xDB2C, 0x424C, { 0xB0, 0x29, 0x7F, 0xE9, 0x9A, 0x87, 0xC6, 0x41 } };

#define USERNAME "apparent_son_of_sparda"
#define PASSWORD "p1zz4s&str4wb3rrysund43s"
#define TIMEOUT_SECONDS 10

void hide_taskbar() 
{

    /* finds a Window by its class name or window name
    HWND FindWindowA(
  [in, optional] LPCSTR lpClassName,
  [in, optional] LPCSTR lpWindowName);
  */

  /* shows or hides a window
  BOOL ShowWindow(
  [in] HWND hWnd,
  [in] int  nCmdShow);
  */

    HWND taskbar = FindWindow("Shell_TrayWnd", NULL);
    if (taskbar) {
        ShowWindow(taskbar, SW_HIDE);
        printf("[+] Haha got your taskbar.\n");
    } else {
        printf("[-] uhhh you dont have your taskbar enabled??\n");
    }
}

void infect_desktop() 
{
    
    /* retrieves the location of a known folder, in our case gets the location of desktop using the FolderID of Desktop
    HRESULT SHGetKnownFolderPath(
  [in]           REFKNOWNFOLDERID rfid,
  [in]           DWORD            dwFlags,
  [in, optional] HANDLE           hToken,
  [out]          PWSTR            *ppszPath);
*/

/*converts windows wide strings to standard c strings
size_t wcstombs(
   char *mbstr,
   const wchar_t *wcstr,
   size_t count);
*/

/* frees memory allocated by COM functions in our case, SHGetKnownFolderPat
void CoTaskMemFree(
  [in, optional] _Frees_ptr_opt_ LPVOID pv
);
*/
    PWSTR desktopPath = NULL;
    if (SUCCEEDED(SHGetKnownFolderPath(&FOLDERID_Desktop, 0, NULL, &desktopPath))) {
        char desktopA[MAX_PATH];
        wcstombs(desktopA, desktopPath, MAX_PATH);
        CoTaskMemFree(desktopPath);

        printf("[+] Spam time yeaaaaaaaaaaaaahhhhhhhhhhhh!!!!!\n");

        for (int i = 0; i < 80; i++) {
            char filePath[MAX_PATH];
            snprintf(filePath, MAX_PATH, "%s\\kryptonite_%02d.txt", desktopA, i);

            FILE* f = fopen(filePath, "w");
            if (f) {
                fputs("BOO! Cryptober 2025 is here", f);
                fclose(f);
            }
        }
    }
}

void open_youtube() 
{
     /* launches or opens a file/url
    ShellExecute(hwnd, "find", "c:\\MyPrograms", NULL, NULL, 0);
    */
    ShellExecute(0, "open", "https://youtu.be/PaDY_u4IcOE?si=5H4DbBULO84Afxf0", NULL, NULL, SW_SHOWNORMAL);
}

void trigger_screensaver() 
{
 // Uses rundll32 to call the LockWorkStation function from user32.dll
// This immediately locks the user's session, simulating a screensaver effect
    printf("[+] Your computer will now take a nap.\n");
    system("rundll32.exe user32.dll,LockWorkStation");
}

int main() {
    char user[50] = {0}, pass[50] = {0};
    time_t start = time(NULL);

    printf("Come on, slowpoke. Youve got %d seconds before things get spicy.\n", TIMEOUT_SECONDS);

    printf("Username: ");
    fflush(stdout);
    time_t user_start = time(NULL);
    while ((time(NULL) - user_start) < TIMEOUT_SECONDS && !fgets(user, sizeof(user), stdin));
    if ((time(NULL) - user_start) >= TIMEOUT_SECONDS) {
        printf("\n[-] Time's Up!\n");
        trigger_screensaver();
        return 0;
    }

    user[strcspn(user, "\n")] = 0;

    printf("Password: ");
    fflush(stdout);
    time_t pass_start = time(NULL);
    while ((time(NULL) - pass_start) < TIMEOUT_SECONDS && !fgets(pass, sizeof(pass), stdin));
    if ((time(NULL) - pass_start) >= TIMEOUT_SECONDS) {
        printf("\n[-] Time's Up!\n");
        trigger_screensaver();
        return 0;
    }

    pass[strcspn(pass, "\n")] = 0;


    if (strcmp(user, USERNAME) == 0 && strcmp(pass, PASSWORD) == 0) {
        printf("[+] ... And Jackpot!\n");
        open_youtube();
    } else {
        printf("[-] Let's go all the way to Hell!\n");
        infect_desktop();
        hide_taskbar();
    }

    return 0;
}
