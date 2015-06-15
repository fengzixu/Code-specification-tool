#pragma once

class KFileWrite
{
public:
    KFileWrite();
    ~KFileWrite();

    BOOL Init(LPCTSTR lpFilePath);
    BOOL WriteToFile(LPCTSTR lpWrite);
    BOOL Uninit();

private:
    FILE* m_pStream;
};
