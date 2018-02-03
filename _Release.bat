C:\Factory\Tools\RDMD.exe /RC out

COPY /B Post\Release\Post.exe out
COPY /B PutFile\Release\PutFile.exe out
COPY /B Uploader\Uploader\bin\Release\Uploader.exe out
COPY /B ..\HTT\Get\Release\Get.exe out
COPY /B ..\HTT\HTT\Release\HTT.exe out
COPY /B ..\HTT\doc\HTT.conf out
COPY /B ..\HTT\doc\NotFound.htm_ out
COPY /B ..\HTT\doc\ServiceUnavailable.htm_ out
COPY /B ..\HTT\doc\MimeType.tsv_ out

C:\Factory\Tools\xcp.exe doc out

C:\Factory\SubTools\zip.exe /O out Uploader

PAUSE
