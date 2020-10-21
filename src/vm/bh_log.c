/*
Copyright ? 2020 <copyright holders>

Permission is hereby granted, free of charge, to any person obtaining 
a copy of this software and associated documentation files (the ¡°Software¡±), 
to deal in the Software without restriction, including without limitation 
the rights to use, copy, modify, merge, publish, distribute, sublicense, 
and/or sell copies of the Software, and to permit persons to whom the Software 
is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all 
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED ¡°AS IS¡±, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, 
INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR 
PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE 
FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR 
OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER 
DEALINGS IN THE SOFTWARE.

Author: chinesebear
Email: swubear@163.com
Website: http://chinesebear.github.io
Date: 2020/8/10
Description: dump/debug funtions for logs.
*/

#include "bh_log.h"

void log_printf (const char* pFileName, unsigned int uiLine, const char* pFnucName, char *LogFmtBuf, ...)
{
	va_list args;
	if(pFileName == NULL || uiLine == 0 || LogFmtBuf == NULL)
	{
		return ;
	}
    char logbuf[256];
	memset (logbuf,'\0',256);
	sprintf (logbuf,"%s:%d, %s(), ", pFileName, uiLine, pFnucName);	
	printf ("%s",logbuf);
	memset (logbuf,'\0',256);
	va_start (args, LogFmtBuf);
	vsnprintf (logbuf, 256, LogFmtBuf, args); 
	va_end (args);
	printf ("%s\r\n",logbuf);
}

void log_data(const char *pFileName, unsigned int uiLine, const char* pFnucName, const char *pcStr,unsigned char *pucBuf,unsigned int usLen)
{
    unsigned int i;
    unsigned char acTmp[17];
    unsigned char *p;
    unsigned char *pucAddr = pucBuf;

    if(pcStr)
    {
        log_printf (pFileName, uiLine, pFnucName, "[%s]: length = %d (0x%X)\r\n",pcStr, usLen, usLen);
    }
    if(usLen == 0)
    {
        return;
    }
    p = acTmp;
    printf ("    %p  ", pucAddr);
    for(i=0;i<usLen;i++)
    {

        printf ("%02X ",pucBuf[i]);
        if((pucBuf[i] >= 0x20) && (pucBuf[i] < 0x7F))
        {
            *p++ = pucBuf[i];
        }
        else
        {
            *p++ = '.';
        }
        if((i+1)%16==0)
        {
            *p++ = 0;
            printf ("        | %s", acTmp);
            p = acTmp;

            printf ("\r\n");

            if((i+1) < usLen)
            {
                pucAddr += 16;
                printf ("    %p  ", pucAddr);
            }
        }
        else if((i+1)%8==0)
        {
            printf ("- ");
        }
    }
    if(usLen%16!=0)
    {
        for(i=usLen%16;i<16;i++)
        {
            printf ("   ");
            if(((i+1)%8==0) && ((i+1)%16!=0))
            {
                printf ("- ");
            }
        }
        *p++ = 0;
        printf ("        | %s", acTmp);
        printf ("\r\n");
    }
    printf ("\r\n");
}


