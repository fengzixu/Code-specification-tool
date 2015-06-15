#include "stdafx.h"
#include "KCommonFunction.h"
#include <queue>


BOOL KCommonFunction::CreateDeepDirectory(LPCTSTR szPath)
{
    BOOL bRetCode = FALSE;
    CString strPath(szPath);

    if (GetFileAttributes(szPath) != INVALID_FILE_ATTRIBUTES)
        return TRUE;

    bRetCode = ::CreateDirectory(szPath, NULL);
    if (!bRetCode && ::GetLastError() != ERROR_ALREADY_EXISTS)
    {
        PathRemoveFileSpec(strPath);
        if (strPath.IsEmpty()) return FALSE;

        bRetCode = CreateDeepDirectory(strPath);
        if (!bRetCode) return FALSE;

        bRetCode = ::CreateDirectory(szPath, NULL);
        if (!bRetCode && ::GetLastError() != ERROR_ALREADY_EXISTS)
            return FALSE;
    }

    return TRUE;
}

void KCommonFunction::PathRemoveFileSpec(CString& strPath)
{
    int nPos = strPath.ReverseFind(_T('\\'));
    if (nPos == -1)
        strPath.Empty();
    else
        strPath = strPath.Left(nPos);
}

void KCommonFunction::PathAddBackslash(CString& strPath)
{
    if (strPath.IsEmpty()) return;

    TCHAR ch = strPath.GetAt(strPath.GetLength() - 1);
    if (ch != _T('\\') && ch != _T('/'))
        strPath += _T("\\");
}

BOOL KCommonFunction::SearchAllFiles(LPCTSTR lpDir, 
                                     std::vector<CString>& vecAllDir,
                                     std::vector<CString>& vecAllFilePath)
{
    std::queue<CString> DirQueue;
    BOOL bRetCode = FALSE;
    vecAllDir.clear();
    vecAllFilePath.clear();
    DirQueue.push((CString)lpDir);

    while (!DirQueue.empty())
    {
        CString strFirstDir = DirQueue.front();
        DirQueue.pop();

        CString strFirstFileName = strFirstDir + _T("\\*");
        WIN32_FIND_DATA finddata = {0};
        HANDLE hFile = ::FindFirstFile(strFirstFileName, &finddata);
        if (INVALID_HANDLE_VALUE == hFile)
            continue;

        do
        {
            CString strFileName = finddata.cFileName;
            if (0 == strFileName.CompareNoCase(_T(".")) || 0 == strFileName.CompareNoCase(_T("..")))
                continue;

            CString strFilePath = strFirstDir + _T("\\") + strFileName;
            if (::PathIsDirectory(strFilePath))
            {
                vecAllDir.push_back(strFilePath);
                DirQueue.push(strFilePath);
            }
            else
                vecAllFilePath.push_back(strFilePath);

        } while (::FindNextFile(hFile, &finddata));
        ::FindClose(hFile);
    }

    return TRUE;
}
