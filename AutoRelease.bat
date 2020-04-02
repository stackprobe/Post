IF NOT EXIST Uploader_is_here.sig GOTO END
CLS
rem リリースして qrum します。
PAUSE

CD /D ..\HTT

IF NOT EXIST HTT_is_here.sig GOTO END

CALL qq
cx **

CD /D %~dp0.

IF NOT EXIST Uploader_is_here.sig GOTO END

CALL qq
cx **

CALL _Release.bat /-P

MOVE out\Uploader.zip S:\リリース物\.

START "" /B /WAIT /DC:\home\bat syncRev

CALL qrumauto rel

rem **** AUTO RELEASE COMPLETED ****

:END
