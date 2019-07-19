extern void InitializeConstructors();
extern void Exit();

extern void AppMain();

extern "C" void Main()
{
    InitializeConstructors();
    AppMain();
    Exit();

    for (;;);
}