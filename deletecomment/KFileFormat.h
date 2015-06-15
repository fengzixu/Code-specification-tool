#pragma once

#define         SINGLE_LINE_COMMENT          _T("//")
#define         LEFT_MULTI_LINE_COMMENT      _T("/*")
#define         RIGHT_MULTI_LINE_COMMENT     _T("*/")
#define         EMPTY_STRING                 _T("")
#define         QUATATION                    _T('"')

#include <vector>

class KFileFormat
{
public:
    BOOL Init(LPCTSTR lpFilePath);
    BOOL DeleteComment();
    BOOL Report(LPCTSTR lpOutFilePath);

private:
    BOOL _DeleteCurrentLineComment(LPCTSTR lpOristr, CString& strDesStr, BOOL* pbDeleteMode);
    BOOL _WriteToFile(LPCTSTR lpOutputPath, LPCTSTR lpWriteContent);
    int _Min(int nNum1, int nNum2);
    BOOL _IsCommentInvalid(LPCTSTR lpOristr, int nIndex);

private:
    std::vector<CString> m_vecLine;
};
