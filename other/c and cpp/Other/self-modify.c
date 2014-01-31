#include <windows.h>
#include <stdio.h>

int main(int argc, char * argv[])
{
    char self[_MAX_PATH];  
    char swap[_MAX_PATH];
    
    // get the full path of myself
    GetModuleFileName(NULL, self, _MAX_PATH);

    // copy myself to a temp file for modify 
    strcpy(swap, self);
    strcat(swap, ".tmp");
    CopyFile(self, swap, FALSE);
    
    FILE * fp = fopen(swap, "ab");
    // do whatever you want on the exe
    fwrite("crack is not good", 18, 1, fp);
    fclose(fp);
    
    // "ping" is used for delay to wait the main process terminated.
    // "move /Y src dst" : overide whtout warnning
    // quotation marks are needed for paths which contain blank.
    char bat[2*_MAX_PATH + 30] = "cmd /c ping 127.0.0.1 -n 2 >nul && move /Y \"";
    strcat(bat, swap);
    strcat(bat, "\"");
    strcat(bat, " \"");
    strcat(bat, self);
    strcat(bat, "\"");

    WinExec(bat, SW_HIDE);

    return 0;
}
