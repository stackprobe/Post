#include "all.h"

static int CompFileName(char *file1, char *file2)
{
	return mbs_stricmp(file1, file2);
}
static int CompFileExt(char *file1, char *file2)
{
	int ret = mbs_stricmp(getExt(file1), getExt(file2));

	if(!ret)
		ret = CompFileName(file1, file2);

	return ret;
}
static int CompFileSize(char *file1, char *file2)
{
	__int64 size1 = getFileSize(file1);
	__int64 size2 = getFileSize(file2);

	int ret = m_simpleComp(size1, size2); // 小さい順

	if(!ret)
		ret = CompFileName(file1, file2);

	return ret;
}
static int CompFileModifyTime(char *file1, char *file2)
{
	updateFindData(file1);
	time_t mTime1 = m_max(lastFindData.time_create, lastFindData.time_write);
	updateFindData(file2);
	time_t mTime2 = m_max(lastFindData.time_create, lastFindData.time_write);

	int ret = m_simpleComp(mTime2, mTime1); // 新しい順

	if(!ret)
		ret = CompFileName(file1, file2);

	return ret;
}
static int CompFileWriteTime(char *file1, char *file2)
{
	updateFindData(file1);
	time_t wTime1 = lastFindData.time_write;
	updateFindData(file2);
	time_t wTime2 = lastFindData.time_write;

	int ret = m_simpleComp(wTime2, wTime1); // 新しい順

	if(!ret)
		ret = CompFileName(file1, file2);

	return ret;
}
static autoList<char *> *GetUploadedFiles(int sort_order = SortOrder)
{
	cout("sort_order: %d\n", sort_order);

	autoList<char *> *files = ls(UploadDir);

	switch(sort_order)
	{
	case 0: files->Sort(CompFileModifyTime); break;
	case 1: files->Sort(CompFileModifyTime); files->Reverse(); break;
	case 2: files->Sort(CompFileName); break;
	case 3: files->Sort(CompFileName); files->Reverse(); break;
	case 4: files->Sort(CompFileExt); break;
	case 5: files->Sort(CompFileExt); files->Reverse(); break;
	case 6: files->Sort(CompFileSize); break;
	case 7: files->Sort(CompFileSize); files->Reverse(); break;
	case 8: files->Sort(CompFileWriteTime); break;
	case 9: files->Sort(CompFileWriteTime); files->Reverse(); break;
	case 10: Shuffle(files); break;

	default:
		error();
	}
	return files;
}
static __int64 GetDiskFree(int drive)
{
	updateDiskSpace(drive);
	cout("lastDiskFree: %I64u (drive: %c)\n", lastDiskFree, drive);

	__int64 ret = (__int64)lastDiskFree;
	errorCase(ret < 0);
	return ret;
}
static __int64 GetDiskFree_ASz(int drive, __int64 appendixSize)
{
	__int64 ret = GetDiskFree(drive);
	ret -= appendixSize;
	cout("diskFree_ASz: %I64d (ASz: %I64d)\n", ret, appendixSize);
	return ret;
}
static __int64 GetUploadDirFree(__int64 uploadDirSize)
{
	__int64 dirSizeMax = UploadDirSizeMax;
	__int64 dirSize = uploadDirSize;
	__int64 dirFree = dirSizeMax - dirSize;
	__int64 diskRealFreeMin = UploadDiskFreeMin;
	__int64 diskRealFree = GetDiskFree(UploadDir[0]);
	__int64 diskFree = diskRealFree - diskRealFreeMin;
	__int64 ret = m_min(dirFree, diskFree);

	cout("UploadDirFree():\n");
	cout("\t""diskSizeMax     ==> %I64d\n", dirSizeMax);
	cout("\t""dirSize         ==> %I64d\n", dirSize);
	cout("\t""dirFree         ==> %I64d\n", dirFree);
	cout("\t""diskRealFreeMin ==> %I64d\n", diskRealFreeMin);
	cout("\t""diskRealFree    ==> %I64d\n", diskRealFree);
	cout("\t""diskFree        ==> %I64d\n", diskFree);
	cout("\t""ret             ==> %I64d\n", ret);

	return ret;
}
static __int64 GetTotalFileSize(autoList<char *> *files, __int64 appendixSize)
{
	__int64 totalSize = appendixSize;

	for(int index = 0; index < files->GetCount(); index++)
	{
		char *file = files->GetElement(index);

		if(!_stricmp(getLocalPath(file), INDEX_FILE))
			continue;

		totalSize += getFileSize(file);
	}
	cout("totalSize: %I64d\n", totalSize);
	errorCase(totalSize < 0);
	return totalSize;
}
static char *EncodeUrl_x(char *href)
{
	autoList<char> *buff = new autoList<char>();

	for(char *p = href; *p; p++)
	{
		if(isMbc(p))
		{
			buff->AddElement(p[0]);
			buff->AddElement(p[1]);
			p++;
		}
		else if(
			'0' <= *p && *p <= '9' ||
			'A' <= *p && *p <= 'Z' ||
			'a' <= *p && *p <= 'z' ||
			*p == '-' ||
			*p == '.' ||
			*p == '/' ||
			*p == ':' ||
			*p == '_'
			)
		{
			buff->AddElement(*p);
		}
		else
		{
			char *encChar = xcout("%%%02x", *p);
			buff->AddElements(encChar, 3);
			memFree(encChar);
		}
	}
	memFree(href);

	buff->AddElement('\0');
	char *ret = buff->UnbindBuffer();
	delete buff;
	return ret;
}
static char *DecodeUrl_x(char *href)
{
	autoList<char> *buff = new autoList<char>();

	for(char *p = href; *p; p++)
	{
		if(*p == '%' && p[1] && p[2])
		{
			buff->AddElement(m_c2i(p[1]) << 4 | m_c2i(p[2]));
			p += 2;
		}
		else
		{
			buff->AddElement(*p);
		}
	}
	memFree(href);

	buff->AddElement('\0');
	char *ret = buff->UnbindBuffer();
	delete buff;
	return ret;
}

// ====>

static void LoadDataFile(void)
{
	char *datFile = strx(getSelfFile());
	removeExt(datFile);
	datFile = addToken(datFile, ".dat");

	FILE *fp = fileOpen(datFile, "rt");

	UploadedFileNumMax = s2i_x(neReadLine(fp));
	UploadDirSizeMax = s2i64_x(neReadLine(fp));
	UploadDiskFreeMin = s2i64_x(neReadLine(fp));
	UploadDir = getFullPath(neReadLine(fp), getSelfDir());
	IndexFormatFile = getFullPath(neReadLine(fp), getSelfDir());
	ResponseHtmlFile = getFullPath(neReadLine(fp), getSelfDir());
	ShowedImageTotalSizeMax = s2i64_x(neReadLine(fp));
	ImageExts = resTokenize_xc(neReadLine(fp), ".");

	{
		char *line = neReadLine(fp);
		int chr = line[0];
		memFree(line);
		Lang_t lang;
		switch(chr)
		{
		case 'E': lang = LANG_E; break;
		case 'J': lang = LANG_J; break;

		default:
			error();
		}
		DateLang = lang;
	}
	ShowDeleteButtonFlag = s2i_x(neReadLine(fp));
	HTTPassword = neReadLine(fp);
	NoOverwriteFlag = s2i_x(neReadLine(fp));
	ShowDownloadLinkFlag = s2i_x(neReadLine(fp));
	SortOrder = s2i_x(neReadLine(fp));
	NoUpFaviconFlag = s2i_x(neReadLine(fp));

	fileClose(fp);

	cout("UploadedFileNumMax: %d\n", UploadedFileNumMax);
	cout("UploadDirSizeMax: %I64d\n", UploadDirSizeMax);
	cout("UploadDiskFreeMin: %I64d\n", UploadDiskFreeMin);
	cout("UploadDir: %s\n", UploadDir);
	cout("IndexFormatFile: %s\n", IndexFormatFile);
	cout("ResponseHtmlFile: %s\n", ResponseHtmlFile);
	cout("ShowedImageTotalSizeMax: %I64d\n", ShowedImageTotalSizeMax);
	cout("ImageExts: %d\n", ImageExts->GetCount());
	cout("DateLang: %d\n", DateLang);
	cout("ShowDeleteButtonFlag: %d\n", ShowDeleteButtonFlag);
	cout("HTTPassword: [%s]\n", HTTPassword);
	cout("NoOverwriteFlag: %d\n", NoOverwriteFlag);
	cout("ShowDownloadLinkFlag: %d\n", ShowDownloadLinkFlag);
	cout("SortOrder: %d\n", SortOrder);

	errorCase(UploadedFileNumMax < 1);
	errorCase(UploadDirSizeMax < 0);
	errorCase(UploadDiskFreeMin < 0);
	errorCase(!existDir(UploadDir));
	errorCase(!existFile(IndexFormatFile));
	errorCase(!existFile(ResponseHtmlFile));
	errorCase(ShowedImageTotalSizeMax < 0);
	// ImageExts
	// DateLang
	// ShowDeleteButtonFlag
	// HTTPassword
	// NoOverwriteFlag
	// ShowDownloadLinkFlag

	memFree(datFile);
}
static void SlimmingDownUploadDir(int fileNumPlus, __int64 fileSizePlus)
{
	autoList<char *> *files = GetUploadedFiles(0); // 新しい順

	LOGPOS();
	cout(
		"\t""condition:\n"
		"\t""fileNumPlus: %d\n"
		"\t""files: %d\n"
		"\t""UploadedFileNumMax: %d\n"
		"\t""UploadDiskFreeMin: %I64d\n"
		"\t""UploadDirSizeMax: %I64d\n"
		"\t""fileSizePlus: %I64d\n"
		,fileNumPlus
		,files->GetCount()
		,UploadedFileNumMax
		,UploadDiskFreeMin
		,UploadDirSizeMax
		,fileSizePlus
		);

	while(
		0 < files->GetCount() &&
		(
			UploadedFileNumMax < files->GetCount() + fileNumPlus ||
			GetDiskFree_ASz(UploadDir[0], fileSizePlus) < UploadDiskFreeMin ||
			UploadDirSizeMax < GetTotalFileSize(files, fileSizePlus)
			)
		)
	{
		char *file = files->UnaddElement();

		cout("オーバーフローによる削除: %s\n", file);
		errorCase_m(
			NoOverwriteFlag,
			"アップロードに必要なディスクの空き領域を確保しようとしましたが、<br/>"
			"上書き禁止モードであるため、失敗しました。<br/>"
			"或いは、リストの更新に失敗"
			);

		removeFile(file);
		memFree(file);
	}
	LOGPOS();

	errorCase_m(
		GetDiskFree_ASz(UploadDir[0], fileSizePlus) < UploadDiskFreeMin,
		"アップロードされたファイルを追加するために必要なディスクの空き領域を確保出来ませんでした。<br/>"
		"或いは、リストの更新に失敗<br/>"
		"（空き領域確保のための削除シーケンスは実行されました）"
		); // 空き領域を確保できなかった。
	errorCase_m(
		UploadDirSizeMax < GetTotalFileSize(files, fileSizePlus),
		"アップロードされたファイルは大きすぎます。<br/>"
		"或いは、リストの更新に失敗<br/>"
		"（空き領域確保のための削除シーケンスは実行されました）"
		); // 合計サイズの上限を超える。

	releaseList(files, (void (*)(char *))memFree);
}
static void MoveUploadDataFile(void)
{
	char *destPath = neReadLine(UPLOADLOCALPATH_FILE);

	destPath = UTF8ToSJIS_x(destPath);
	destPath = getLocalPath_x(destPath);
	destPath = makeFairLocalPath_x(destPath);
	destPath = combine_cx(UploadDir, destPath);

	if(
		!_stricmp(getLocal(destPath), INDEX_FILE) ||
		NoUpFaviconFlag &&
		!_stricmp(getLocal(destPath), "favicon.ico")
		)
		destPath = addChar(destPath, '_');

	cout("destPath: %s\n", destPath);
	errorCase_m(
		250 < strlen(destPath),
		"アップロードされたファイルの名前が長すぎます。<br/>"
		"アップロード先フォルダのパスを短くするか、アップロードするファイルの名前を短くして下さい。"
		);

	if(existDir(destPath))
	{
		errorCase_m(
			NoOverwriteFlag,
			"アップロードされたファイルと同じ名前のフォルダが存在したため、削除しようとしましたが、<br/>"
			"上書き禁止モードであるため、削除出来ませんでした。<br/>"
			"当該フォルダを削除するか、アップロードするファイルの名前を変更して下さい。"
			);
		forceRemoveDir(destPath);
	}
	else if(existFile(destPath))
	{
		if(NoOverwriteFlag)
		{
			destPath = addToken_x(destPath, xcout(".%s.%I64d.0%s", ClientIP, time(NULL), getExtWithDot(destPath)));
			cout("destPath_1: %s\n", destPath);
			errorCase_m(
				250 < strlen(destPath),
				"アップロードされたファイルの名前が長すぎます。<br/>"
				"アップロード先フォルダのパスを短くするか、アップロードするファイルの名前を短くして下さい。<br/>"
				"（上書き禁止モードでなければ、アップロードできたかもしれません）"
				);
			destPath = toCreatablePath(destPath);
			cout("destPath_2: %s\n", destPath);
		}
		else
		{
			char *escPath = strx(destPath);
			escPath = toCreatablePath(escPath);
			cout("escPath: %s\n", escPath);
			errorCase_m(
				250 < strlen(escPath),
				"アップロードされたファイルの名前が長すぎます。<br/>"
				"アップロード先フォルダのパスを短くするか、アップロードするファイルの名前を短くして下さい。<br/>"
				"（ファイルの重複が無ければ、アップロードできたかもしれません）"
				);

			fileMove(destPath, escPath);

			memFree(escPath);
		}
	}

	/*
		移動元(TMP)と移動先(UploadDir)のドライブが異なる場合、移動先がパンクしないか？ @ 2015.11.10
		<- 事前にスリムダウンしてるよ！！！
	*/
	fileMove(UPLOADDATA_FILE, destPath);

	/*
		アクセス権フリー
	*/
	{
		addCwd(UploadDir);
		char *commandLine = xcout("ECHO Y|CACLS \"%s\" /P Users:F Guest:F", getLocalPath(destPath));
		cout("$ %s\n", commandLine);
		system(commandLine);
		memFree(commandLine);
		unaddCwd();
	}

	memFree(destPath);
}
static void DeleteUploadedFile(void)
{
	char *delPath = neReadLine(DELETELOCALPATH_FILE);

	delPath = UTF8ToSJIS_x(delPath);
	delPath = DecodeUrl_x(delPath);
	delPath = getLocalPath_x(delPath);
	delPath = makeFairLocalPath_x(delPath);
	delPath = combine_cx(UploadDir, delPath);
	cout("delPath: %s\n", delPath);

	removeFile(delPath);

	memFree(delPath);
}
static void LoadIndexFormatFile(void)
{
	IndexData = untokenize_xc(readLines(IndexFormatFile), "\n");
}
static void MakeIndex(void)
{
	autoList<char *> *files = GetUploadedFiles();
	autoList<char *> *lines = new autoList<char *>();
	__int64 fileTotalSize = 0;
	__int64 imageTotalSize = 0;
	int fileCount = 0;

	for(int index = 0; index < files->GetCount(); index++)
	{
		char *file = files->GetElement(index);
		char *localFile = getLocalPath(file);

		if(!_stricmp(localFile, INDEX_FILE))
			continue;

		updateFindData(file);
		char *lStamp = getDateTimeStamp(m_max(lastFindData.time_create, lastFindData.time_write));

		if(DateLang == LANG_J)
			lStamp = makeJStamp_x(lStamp);

		__int64 fileSize = getFileSize(file);
		char *lSize = thousandComma(xcout("%I64u", fileSize));
		fileTotalSize += fileSize;

		char *lFHref = strx(localFile);
		lFHref = EncodeUrl_x(lFHref);

		char *lFText = strx(localFile);
		lFText = replace(lFText, "&", "&amp;");

		char *line = xcout(
			"<div>%s　<a href=\"%s\">%s</a>　%s bytes"
			,lStamp
			,lFHref
			,lFText
			,lSize
			);

		if(ShowDownloadLinkFlag)
		{
			line = addToken_x(line, xcout(
				"　<a href=\"%s\" download=\"%s\">[download]</a>"
				,lFHref
				,localFile
				));
		}
		if(ShowDeleteButtonFlag)
		{
			line = addToken_x(line, xcout(
				"　"
				"<form method=\"post\" action=\"/\" accept-charset=\"UTF-8\" enctype=\"multipart/form-data\">"
				"<input type=\"hidden\" name=\"delete\" value=\"%s\"/>"
				"<input type=\"submit\" value=\"削除\"/>%s"
				"</form>"
				,lFHref
				,*HTTPassword ? " / PWD:<input type=\"password\" name=\"password\"/>" : ""
				));
		}
		if(
			1 <= fileSize &&
			getIndex(ImageExts, getExt(file), (int (*)(char *, char *))_stricmp) != -1
			)
		{
			imageTotalSize += fileSize;

			if(imageTotalSize <= ShowedImageTotalSizeMax)
			{
				line = addToken_x(line, xcout(
					"<br/><a href=\"%s\"><img src=\"%s\"/></a>"
					,lFHref
					,lFHref
					));
			}
		}
		line = addToken(line, "</div>");
		lines->AddElement(line);

		fileCount++;

		memFree(lStamp);
		memFree(lSize);
		memFree(lFHref);
		memFree(lFText);
	}
	char *fileLinkListPtn = untokenize_xc(lines, "\n");
	char *fileNumPtn = thousandComma(xcout("%u", (uint)fileCount));
	char *fileTotalSizePtn = thousandComma(xcout("%I64u", (uint64)fileTotalSize));

	int fileNumFree = UploadedFileNumMax - fileCount;
	__int64 dirFree = GetUploadDirFree(fileTotalSize);

	char *fileNumFreePtn = thousandComma(xcout("%u", (uint)fileNumFree));
	char *dirFreePtn = thousandComma(xcout("%I64u", (uint64)dirFree));

	IndexData = replace(IndexData, "$(uploaded-file-list)", fileLinkListPtn, 1);
	IndexData = replace(IndexData, "$(uploaded-file-num)", fileNumPtn, 1);              // アップロードされたファイルの数
	IndexData = replace(IndexData, "$(uploaded-file-total-size)", fileTotalSizePtn, 1); // アップロードされたファイルのサイズ(合計)[byte]
	IndexData = replace(IndexData, "$(file-num-free)", fileNumFreePtn, 1); // アップロード可能なファイルの数
	IndexData = replace(IndexData, "$(dir-free)", dirFreePtn, 1);          // アップロード可能なファイルのサイズ(残りの領域)[byte]
	IndexData = replace(
		IndexData,
		"$(password)",
		*HTTPassword ? " / PWD:<input type=\"password\" name=\"password\"/>" : "",
		1
		);
	IndexData = replace(IndexData, "$(no-overwrite)", NoOverwriteFlag ? "[上書き禁止]" : "", 1);

	releaseList(files, (void (*)(char *))memFree);
	memFree(fileLinkListPtn);
	memFree(fileNumPtn);
	memFree(fileTotalSizePtn);
	memFree(fileNumFreePtn);
	memFree(dirFreePtn);
}
static void WriteIndexFile(void)
{
	char *indexFile = combine(UploadDir, INDEX_FILE);
	cout("indexFile: %s\n", indexFile);
	if(existDir(indexFile)) forceRemoveDir(indexFile); // 2bs
	writeLine(indexFile, IndexData);
	memFree(indexFile);
}
static void MakeResponse(void)
{
	char *text = readText(ResponseHtmlFile);
	WriteResponseHtmlFile(text);
	memFree(text);
}

// <====

static void CheckPassword(void)
{
	if(*HTTPassword) // ? パスワード有効
	{
		char *password = neReadLine(PASSWORD_FILE);

		password = UTF8ToSJIS_x(password);
		password = toJToken_x(password, '\x20', '\x7e');

		cout("password: [%s]\n", password);

		if(strcmp(password, HTTPassword)) // ? パスワードが違う
		{
			cout("WrongPwdWait_start\n");
			Sleep(2000);
			cout("WrongPwdWait_end\n");

			error_m("パスワードが間違っています。");
		}
		memFree(password);
	}
}

int main(int argc, char **argv)
{
	errorCase(!existFile(IP_FILE));
	errorCase(!existFile(RECV_FILE));
	errorCase(!existFile(SEND_FILE));
	ClientIP = neReadLine(IP_FILE);
	SendFileFullPath = getFullPath(SEND_FILE);

	LoadDataFile();

	if(argIs("/E:02"))
	{
		LOGPOS();
		char *indexFile = combine(UploadDir, INDEX_FILE);

		if(!existFile(indexFile))
		{
			LOGPOS();
			LoadIndexFormatFile();
			MakeIndex();
			WriteIndexFile();
		}
		memFree(indexFile);
		LOGPOS();
		termination(0);
	}

	if(existFile(UPLOADDATA_FILE))
	{
		UploadDataSize = getFileSize(UPLOADDATA_FILE);
		cout("UploadDataSize: %I64d\n", UploadDataSize);
		errorCase(_I64_MAX - UploadDiskFreeMin < UploadDataSize); // overflow
	}
	SlimmingDownUploadDir(0, 0);

	if(
		existFile(UPLOADDATA_FILE) &&
		existFile(UPLOADLOCALPATH_FILE)
		)
	{
		CheckPassword();
		SlimmingDownUploadDir(1, UploadDataSize);
		MoveUploadDataFile();
	}
	if(existFile(DELETELOCALPATH_FILE))
	{
		errorCase_m(
			!ShowDeleteButtonFlag,
			"削除ボタンは無効です。"
			);
		CheckPassword();
		DeleteUploadedFile();
	}
	LoadIndexFormatFile();
	MakeIndex();
	WriteIndexFile();
	MakeResponse();

	termination(0);
	return 0; // dummy
}
