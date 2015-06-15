#include "stdafx.h"
#include "KFileWrite.h"
#include <locale.h>

KFileWrite::KFileWrite()
{
    m_pStream = NULL;
}

KFileWrite::~KFileWrite()
{
}

BOOL KFileWrite::Init(LPCTSTR lpFilePath)
{
    if (!lpFilePath)
        return FALSE;

    errno_t err;
    err = _wfreopen_s(&m_pStream, lpFilePath, _T("w"), stdout);
    if (0 != err)
        return FALSE;

    return TRUE;
}

BOOL KFileWrite::WriteToFile(LPCTSTR lpWrite)
{
    if (!lpWrite)
        return FALSE;

    setlocale(LC_ALL, "chs");
    wprintf(L"%ws", lpWrite);

    return TRUE;
}

BOOL KFileWrite::Uninit()
{
    fclose(m_pStream);
    m_pStream = NULL;
    return TRUE;
}
