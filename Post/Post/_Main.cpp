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

	if(getFileSize(IP_FILE) == 0) // ? ������s
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
				���o���ɓǂ܂Ȃ��悤�ɂ����ֈړ����Ă����B
				����̏C���ɉ����Ă����ƑO�Ɉړ����邱�ƁB
				���̂Ƃ���ŏ��� ParseRecvFile() �Ŏg����B
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
