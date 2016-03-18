@echo off
del "bundle\hypnovocabulary.exe"
forfiles /P C:\Tmp /M build-hypnovocabulary-* /C "cmd /c if @isdir==TRUE rmdir /s /q @file"
