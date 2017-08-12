typedef enum Lang_et
{
	LANG_E,
	LANG_J,
}
Lang_t;

extern int UploadedFileNumMax;
extern __int64 UploadDirSizeMax;
extern __int64 UploadDiskFreeMin;
extern char *UploadDir;
extern char *IndexFormatFile;
extern char *ResponseHtmlFile;
extern __int64 ShowedImageTotalSizeMax;
extern autoList<char *> *ImageExts;
extern Lang_t DateLang;
extern int ShowDeleteButtonFlag;
extern char *HTTPassword;
extern int NoOverwriteFlag;
extern int ShowDownloadLinkFlag;
extern int SortOrder;
extern int NoUpFaviconFlag;

extern char *ClientIP;
extern char *SendFileFullPath;
extern __int64 UploadDataSize;
extern char *IndexData;

void WriteResponseHtmlFile(char *text);
