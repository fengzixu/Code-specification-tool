#include "stdafx.h"
#include "KFileFormat.h"
#include "KReadFile.h"
#include "KFileWrite.h"

BOOL KFileFormat::Init(LPCTSTR lpFilePath)
{
    if (!lpFilePath)
        return FALSE;

    KReadFile readfile;
    if (!readfile.Init(lpFilePath))
        return FALSE;

    CString strLine;
    while (readfile.GetLine(strLine))
    {
        m_vecLine.push_back(strLine);
    }

    return readfile.Uninit();
}

BOOL KFileFormat::DeleteComment()
{
    BOOL bIsDeleteMode = FALSE;
    for (int i = 0; i < (int)m_vecLine.size(); i++)
    {
        CString strLine = m_vecLine[i];
        if (strLine.IsEmpty())
            continue;

        if (TRUE == bIsDeleteMode)
        {
            int nIndexRightMultiComment = strLine.Find(RIGHT_MULTI_LINE_COMMENT);
            if (-1 != nIndexRightMultiComment)
            {
                m_vecLine[i] = strLine.Mid(nIndexRightMultiComment + 2);
                bIsDeleteMode = FALSE;
            }
            else
                m_vecLine[i] = EMPTY_STRING;

            continue;
        }

        _DeleteCurrentLineComment(strLine, m_vecLine[i], &bIsDeleteMode);
    }
    return TRUE;
}

BOOL KFileFormat::_DeleteCurrentLineComment(LPCTSTR lpOristr, CString& strDesStr, BOOL* pbDeleteMode)
{
    if (!lpOristr || !pbDeleteMode)
        return FALSE;

    CString strLine = lpOristr;
    while (1)
    {
        int nIndexSingleComment = 0;
        while (1)
        {
            nIndexSingleComment = strLine.Find(SINGLE_LINE_COMMENT, nIndexSingleComment);
            if (-1 == nIndexSingleComment)
                break;
            if (FALSE == _IsCommentInvalid(strLine, nIndexSingleComment))
                break;
            nIndexSingleComment++;
        }

        int nIndexLeftMultiComment = 0;
        while (1)
        {
            nIndexLeftMultiComment = strLine.Find(LEFT_MULTI_LINE_COMMENT, nIndexLeftMultiComment);
            if (-1 == nIndexLeftMultiComment)
                break;
            if (FALSE == _IsCommentInvalid(strLine, nIndexLeftMultiComment))
                break;
            nIndexLeftMultiComment++;
        }

        if (-1 == nIndexSingleComment && -1 == nIndexLeftMultiComment)
            break;

        int nMin = _Min(nIndexSingleComment, nIndexLeftMultiComment);
        if (nMin == nIndexSingleComment)
        {
            strLine = strLine.Left(nIndexSingleComment);
            continue;
        }

        *pbDeleteMode = TRUE;
        int nIndexRightMultiComment = strLine.Find(RIGHT_MULTI_LINE_COMMENT, nIndexLeftMultiComment + 2);
        if (-1 != nIndexRightMultiComment)
            *pbDeleteMode = FALSE;

        strLine = *pbDeleteMode == TRUE ? strLine.Left(nIndexLeftMultiComment) : 
            strLine.Left(nIndexLeftMultiComment) + strLine.Mid(nIndexRightMultiComment + 2);
    }
    strDesStr = strLine;
    return TRUE;
}

BOOL KFileFormat::Report(LPCTSTR lpOutFilePath)
{
    if (!lpOutFilePath)
        return FALSE;

    CString strFinalOutput;
    for (int i = 0; i < (int)m_vecLine.size(); i++)
    {
        strFinalOutput.AppendFormat(L"%s\n", m_vecLine[i]);
    }
    return _WriteToFile(lpOutFilePath, strFinalOutput);
}

BOOL KFileFormat::_WriteToFile(LPCTSTR lpOutputPath, LPCTSTR lpWriteContent)
{
    if (!lpOutputPath || !lpWriteContent)
        return FALSE;

    KFileWrite filewrite;
    if (filewrite.Init(lpOutputPath))
    {
        filewrite.WriteToFile(lpWriteContent);
        filewrite.Uninit();
    }
    return TRUE;
}

int KFileFormat::_Min(int nNum1, int nNum2)
{
    int nMin = 2048;
    if (nNum1 >= 0 && nNum1 < nMin) nMin = nNum1;
    if (nNum2 >= 0 && nNum2 < nMin) nMin = nNum2;
    return nMin;
}

BOOL KFileFormat::_IsCommentInvalid(LPCTSTR lpOristr, int nIndex)
{
    CString strLine(lpOristr);
    std::vector<int> vecPos;
    int nStartPos = 0;
    while (1)
    {
        int nIndex = strLine.Find(QUATATION, nStartPos);
        if (-1 == nIndex)
            break;

        if (nIndex > 0 && ('\'' != strLine.GetAt(nIndex - 1) || '\\' != strLine.GetAt(nIndex - 1)))
            vecPos.push_back(nIndex);
        
        nStartPos = nIndex + 1;
    }
    for (int i = 0; i < (int)vecPos.size(); i += 2)
    {
        if (nIndex > vecPos[i] && (i + 1 < (int)vecPos.size() && nIndex < vecPos[i + 1]))
            return TRUE;
    }
    return FALSE;
}