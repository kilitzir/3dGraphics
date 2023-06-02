pkzip -ex backup.zip *.cpp *.h *.tc *.tcp *.prj *.bat
md backup\%1
xcopy backup.zip backup\%1
