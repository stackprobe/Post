#include "all.h"

// .dat {

int UploadedFileNumMax = 65000;
__int64 UploadDirSizeMax = 9220000000000000000;
__int64 UploadDiskFreeMin = 3000000000;
char *UploadDir;
char *IndexFormatFile;
char *ResponseHtmlFile;
__int64 ShowedImageTotalSizeMax; // 0i64 == ‰æ‘œ‚ð•\Ž¦‚µ‚È‚¢
autoList<char *> *ImageExts;
Lang_t DateLang;
int ShowDeleteButtonFlag;
char *HTTPassword;
int NoOverwriteFlag;
int ShowDownloadLinkFlag;
int SortOrder;
int NoUpFaviconFlag;
int EmbedMovieFlag;
autoList<char *> *MovieExts;
int EmbedMusicFlag;
autoList<char *> *MusicExts;

// }

char *ClientIP;
char *SendFileFullPath;
__int64 UploadDataSize;
char *IndexData;

// ----

void WriteResponseHtmlFile(char *text)
{
	if(!SendFileFullPath)
	{
		LOGPOS();
		return;
	}

	text = strx(text);
	text = replace(text, "\r", "");
	text = replace(text, "\n", "\r\n");

	int textLen = strlen(text);
	FILE *fp = fileOpen(SendFileFullPath, "wb");
	
	writeToken(fp, "HTTP/1.1 200 Happy Tea Time" CRLF);
	writeToken(fp, "Server: htt" CRLF);
	writeToken(fp, "Content-Type: text/html; charset=Shift_JIS" CRLF);
	writeToken_x(fp, xcout("Content-Length: %d" CRLF, textLen));
	writeToken(fp, "Connection: close" CRLF);
	writeToken(fp, CRLF);
	fileWrite(fp, text, textLen);

	fileClose(fp);
	memFree(text);
}
