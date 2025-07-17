#include <stdio.h>
#include <windows.h>
#include <shlobj.h> //provides declaration for shell object functions, used for accessing user/system folders.
#include <time.h>

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
    if (taskbar) 
    ShowWindow(taskbar, SW_HIDE);
    printf("[+] Your taskbar is now hidden.");
    else
    printf("[-] uhhh you dont have your taskbar enabled??");
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

        printf("[+] Spam time yeaaaaaaaaaaaaahhhhhhhhhhhh!!!!!");

        for (int i = 0; i < 20; i++) {
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

void trigger_screensaver() {
    /*sends specified  message to a window or windows
    LRESULT SendMessage(
  [in] HWND   hWnd,
  [in] UINT   Msg,
  [in] WPARAM wParam,
  [in] LPARAM lParam);
  */
    print("[+] Your computer will now take a nap.")
    SendMessage(HWND_BROADCAST, WM_SYSCOMMAND, SC_SCREENSAVE, 0);
}

int main() {
    char user[50] = {0}, pass[50] = {0};
    time_t start = time(NULL);

    printf("[+] You’ve got 10 seconds to enter your creds… or we let Hell take over. Tick tock.\n");

    printf("Username: ");
    fflush(stdout);
    while ((time(NULL) - start) < TIMEOUT_SECONDS && !fgets(user, sizeof(user), stdin));
    if ((time(NULL) - start) >= TIMEOUT_SECONDS) {
        printf("\n[-] It's Showtime!\n");
        trigger_screensaver();
        return 0;
    }

    user[strcspn(user, "\n")] = 0;

    printf("Password: ");
    fflush(stdout);
    while ((time(NULL) - start) < TIMEOUT_SECONDS && !fgets(pass, sizeof(pass), stdin));
    if ((time(NULL) - start) >= TIMEOUT_SECONDS) {
        printf("\n[-] It's Showtime!\n");
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
