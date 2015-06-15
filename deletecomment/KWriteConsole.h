#pragma once

class KWriteConsole
{
public:
    KWriteConsole();
    ~KWriteConsole();

    BOOL Init();
    BOOL WriteToConsole(LPCTSTR lpWrite);
    BOOL Uninit();

private:
    FILE* m_pStream;
};
