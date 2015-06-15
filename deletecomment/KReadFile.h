#pragma once

class KReadFile
{
public:
    KReadFile();
    ~KReadFile();

    BOOL Init(LPCTSTR lpFilePath);
    BOOL GetLine(CString& strLine);
    BOOL Uninit();

private:
    FILE *m_pStream;
};
