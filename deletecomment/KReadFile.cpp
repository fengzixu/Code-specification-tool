#include "StdAfx.h"
#include "KReadFile.h"

KReadFile::KReadFile()
{
    m_pStream = NULL;
}

KReadFile::~KReadFile()
{
}

BOOL KReadFile::Init(LPCTSTR lpFilePath)
{
    if (!lpFilePath)
        return FALSE;

    errno_t err;
    err = _wfreopen_s(&m_pStream, lpFilePath, _T("r"), stdin);

    return err == 0;
}

BOOL KReadFile::GetLine(CString& strLine)
{
    static const int nBufferSize = 2048;
    TCHAR szBuffer[nBufferSize] = {0};
    if (NULL == _getws_s(szBuffer, nBufferSize))
        return FALSE;
    strLine = szBuffer;
    return TRUE;
}

BOOL KReadFile::Uninit()
{
    if (!m_pStream)
        return TRUE;

    int nRet = fclose(m_pStream);
    m_pStream = NULL;
    return nRet == 0;
}
