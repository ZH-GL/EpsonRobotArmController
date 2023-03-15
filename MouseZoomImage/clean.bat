echo off
del Makefile.*
del *.idb
del *.ncb
del *.pdb
del *.sln
del /AH *.suo
del *.suo
del *.ilk
del *.aps
del *.vcproj
del *.vcxproj
del *.filters
del *.sdf
del *.user
del object_script.*
del *.qmake.stash
rmdir /S /Q .klocwork
rmdir /S /Q ui/include
rmdir /S /Q tmp
rmdir /S /Q moc
rmdir /S /Q ui_source
rmdir /S /Q release
rmdir /S /Q debug
rmdir /S /Q GeneratedFiles
rmdir /S /Q pb_source
rmdir /S /Q ipch
rmdir /S /Q .vs
 if "%1" == "autoclose" goto end
 pause
 :end