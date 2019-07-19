#include "Pdb.h"
#include "PdbFile.h"

using namespace Tools::Pdb;

PdbFile::PdbFile(String^ path)
{
    this->path = path;

    if (!File::Exists(path))
        throw gcnew IOException();

	HMODULE hModule = LoadLibrary(L"C:\\Program Files (x86)\\Microsoft Visual Studio\\2019\\Community\\DIA SDK\\bin\\msdia140.dll");
	if (!hModule)
		throw gcnew Exception();

	BOOL(WINAPI* DllGetClassObject)(REFCLSID, REFIID, LPVOID*) = (BOOL(WINAPI*)(REFCLSID, REFIID, LPVOID*))GetProcAddress(hModule, "DllGetClassObject");
	if (!DllGetClassObject)
		throw gcnew Exception();

	CComPtr<IClassFactory> pClassFactory;
	HRESULT hResult = DllGetClassObject(CLSID_DiaSource, IID_IClassFactory, (LPVOID*)&pClassFactory);
	if (FAILED(hResult))
		throw gcnew Exception();

	IDiaDataSource* diaDataSourcePointer = NULL;

	hResult = pClassFactory->CreateInstance(NULL, IID_IDiaDataSource, (void**)&diaDataSourcePointer);
	if (FAILED(hResult))
		throw gcnew Exception();

	diaDataSource = diaDataSourcePointer;

    LPCOLESTR pathStr = (LPCOLESTR)(Marshal::StringToHGlobalUni(path).ToPointer());
    diaDataSource->loadDataFromPdb(pathStr);
}

PdbSession^ PdbFile::OpenSession(ULONGLONG address)
{
    IDiaSession* diaSession = NULL;
    diaDataSource->openSession(&diaSession);

    diaSession->put_loadAddress(address);

    return gcnew PdbSession(diaSession);
}