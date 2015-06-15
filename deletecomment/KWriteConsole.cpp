#include "stdafx.h"
#include "KWriteConsole.h"
#include <locale.h>

KWriteConsole::KWriteConsole()
{
    m_pStream = NULL;
}

KWriteConsole::~KWriteConsole()
{
}

BOOL KWriteConsole::Init()
{
    errno_t err;
    err = _wfreopen_s(&m_pStream, _T("CON"), _T("w"), stdout);
    if (0 != err)
        return FALSE;

    return TRUE;
}

BOOL KWriteConsole::WriteToConsole(LPCTSTR lpWrite)
{
    if (!lpWrite)
        return FALSE;

    setlocale(LC_ALL, "chs");
    wprintf(L"%ws", lpWrite);

    return TRUE;
}

BOOL KWriteConsole::Uninit()
{
    fclose(m_pStream);
    m_pStream = NULL;
    return TRUE;
}
