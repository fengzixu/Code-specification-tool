#pragma once

#include <vector>

class KCommonFunction
{
public:
    static BOOL CreateDeepDirectory(LPCTSTR szPath);
    static void PathRemoveFileSpec(CString& strPath);
    static void PathAddBackslash(CString& strPath);
    static BOOL SearchAllFiles(LPCTSTR lpDir, 
                               std::vector<CString>& vecAllDir,
                               std::vector<CString>& vecAllFilePath);
};
