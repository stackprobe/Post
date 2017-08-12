#include "all.h"

static void ResponseModeMain(void)
{
	setFileSize(RECV_FILE, 0);

	if(getFileSize(SEND_FILE) == 0)
	{
		HTT_Disconnect();
		return;
	}
	errorCase(getFileWriteTime(SEND_FILE) + 60L < time(NULL)); // ? timeout
}
int main(int argc, char **argv)
{
	HomeDir = getCwd();

	errorCase(!existFile(IP_FILE));
	errorCase(!existFile(RECV_FILE));
	errorCase(!existFile(SEND_FILE));
	SendFileFullPath = getFullPath(SEND_FILE);
	ResponseModeFileFullPath = getFullPath(RESPONSEMODE_FILE);

	UserProgram = getFullPath(nextArg(), getSelfDir());
	errorCase(!existFile(UserProgram));

	if(getFileSize(IP_FILE) == 0) // ? 定期実行
		return 0;

	if(existFile(RESPONSEMODE_FILE))
	{
		ResponseModeMain();
		goto endProc;
	}
	errorCase(getFileWriteTime(RECV_FILE) + 60L < time(NULL)); // ? timeout

	if(ParseHeader())
	{
		if(IsRecvEnded())
		{
			removeFile(CHUNKEDMODE_FILE);
			removeFile(RECVFINALSIZE_FILE);

			/*
				小出しに読まないようにここへ移動してきた。
				今後の修正に応じてもっと前に移動すること。
				今のところ最初に ParseRecvFile() で使われる。
			*/
			LoadConfig();

			ParseRecvFile();
			char *commandLine = xcout("\"%s\"", UserProgram);
			system(commandLine);
			memFree(commandLine);
			createFile(RESPONSEMODE_FILE);

			if(getFileSize(SEND_FILE) == 0)
				HTT_Disconnect();
		}
	}
endProc:
	termination(0);
	return 0; // dummy
}
