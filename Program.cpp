#include <iostream>
#include <windows.h>
#include <string>
#include <thread>
#include <libloaderapi.h>


using namespace std;




// Get the process id
void get_proc_id(const char* window_title, DWORD &process_id)
{
    GetWindowThreadProcessId(FindWindow(NULL, window_title), &process_id);
}


// Error sending
void error(const char* error_title, const char* error_message)
{
    MessageBox(0, error_message, error_title, 0);
    exit(-1);
}

// Does the file exist?
bool does_file_exist(string file_name)
{
    struct stat buffer;
    return (stat(file_name.c_str(), &buffer) === 0);
}

int main()
{
    MessageBox(0, "Injector, Made By Raz", 0)
    DWORD proc_id = NULL;
    char dll_path[MAX_PATH];
    // will make a actual dll soon
    const char* dll_name = "placeholder.dll";
    const char* window_title = "Minecraft";
    
    // If the DLL doesnt exist, output an error.
    if (!does_file_exist(dll_name))
    {
        error("does_file_exist", "The requested DLL you want to inject does not exist. Make sure to format it properly.");
    }
    
    // If the DLL does exist, get the path
    if (GetFullPathName(dll_name, MAX_PATH, dll_path, nullptr))
    {
        error("GetFullPathName", "Failed to get the DLLs full path. Reinstall the DLL/Place it in this folder.");
    }
    
    
    // Get the process ID and see if it is a thing.
    get_proc_id(window_title, proc_id);
    if (proc_id == NULL)
    {
        error("get_proc_id", "Failed to get process ID");
    }
    
    // Even more error checking holy shit
    HANDLE h_process = OpenProcess(PROCESS_ALL_ACCESS, NULL, proc_id);
    if (!h_process)
    {
        error("OpenProcess", "Failed to open a handle to process");
    }
    
    // check check check
    void* allocated_memory = VirtualAllocEx(h_process, nullptr, MAX_PATH, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
    if (!allocated_memory)
    {
        error("VirtualAllocEx", "Failed to allocate memory.");
        
    }
    
    if (!WriteProcessMemory(h_process, dll_path, MAX_PATH, nullptr))
    {
        error("WriteProcessMemory", "Failed to write process memory.");
    }
    
    HANDLE h_thread = CreateRemoteThread(h_process, nullptr, NULL, LPTHREAD_START_ROUTINE(LoadLibraryA), allocated_memory, NULL, nullptr);
    if(!h_thread)
    {
        error("CreateRemoteThread", "Failed to create remote thread.");
    }
    CloseHandle(h_process);
    VirtualFreeEx(h_process, allocated_memory, NULL, MEM_RELEASE);
    MessageBox(0, "Injected! You may now close this window.", 0)
}
