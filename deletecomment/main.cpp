// deletecomment.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <locale.h>
#include "KCommonFunction.h"
#include "KFileFormat.h"
#include "KWriteConsole.h"

void WriteToConsole(LPCTSTR lpWrite)
{
    if (!lpWrite)
        return;

    KWriteConsole writeconsole;
    if (writeconsole.Init())
    {
        writeconsole.WriteToConsole(lpWrite);
        writeconsole.Uninit();
    }

}

void ReadFromConsole()
{
    FILE* pStream = NULL;
    errno_t err;
    err = _wfreopen_s(&pStream, _T("CON"), _T("r"), stdin);
}

int _tmain(int argc, _TCHAR* argv[])
{
    std::vector<CString> vecFails;
    int nTotalFiles = 0;

    TCHAR szFileName[MAX_PATH];
    ::GetModuleFileName(NULL, szFileName, MAX_PATH);
    CString strFilter = szFileName;

    ::PathRemoveFileSpec(szFileName);
    CString strOriDir = szFileName;
    CString strDesDir = strOriDir + _T("_bk");
    KCommonFunction::CreateDeepDirectory(strDesDir);

    std::vector<CString> vecAllDir;
    std::vector<CString> vecAllFilePath;
    KCommonFunction::SearchAllFiles(strOriDir, vecAllDir, vecAllFilePath);
    nTotalFiles = (int)vecAllFilePath.size();

    for (int i = 0; i < (int)vecAllDir.size(); i++)
    {
        CString strOriSubDir = vecAllDir[i];
        CString strNewSubDir = strOriSubDir;
        strNewSubDir.Replace(strOriDir, strDesDir);
        KCommonFunction::CreateDeepDirectory(strNewSubDir);
    }

    CString strOutInfo;
    for (int i = 0; i < (int)vecAllFilePath.size(); i++)
    {
        CString strOriFilePath = vecAllFilePath[i];
        if (0 == strOriFilePath.CompareNoCase(strFilter))
        {
            nTotalFiles--;
            continue;
        }

        CString strNewFilePath = strOriFilePath;
        strNewFilePath.Replace(strOriDir, strDesDir);

        strOutInfo.Format(L"Copy: %ws  -->  %ws\n", strOriFilePath, strNewFilePath);
        WriteToConsole(strOutInfo);

        if (FALSE == ::CopyFile(strOriFilePath, strNewFilePath, FALSE))
            vecFails.push_back(strOriDir);

        KFileFormat fileformat;
        if (!fileformat.Init(strNewFilePath))
            continue;

        fileformat.DeleteComment();
        fileformat.Report(strNewFilePath);
    }

    strOutInfo.Format(L"\n--------------------------------------------------------------------------------\n");
    strOutInfo.AppendFormat(L"%d succeeded, %d failed\n", nTotalFiles - vecFails.size(), vecFails.size());
    strOutInfo.AppendFormat(L"\nPress any key to shut console\n");
    WriteToConsole(strOutInfo);

    ReadFromConsole();
    system("pause");
    return 0;
}

