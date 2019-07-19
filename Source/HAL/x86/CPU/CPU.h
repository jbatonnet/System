#if !defined(_CPU_H_) && defined(X86)
#define _CPU_H_

void CPU_Initialize();
void CPU_Shutdown();
char* _CPU_GetVendor();

#endif