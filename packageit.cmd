set STAGING_DIR=STAGING\com.jamesharris.jewelsfree

rmdir /s /y %STAGING_DIR%
del *.ipk
mkdir %STAGING_DIR%

copy appinfo.json %STAGING_DIR%
copy gemz %STAGING_DIR%
echo filemode.755=gemz > %STAGING_DIR%\package.properties
palm-package %STAGING_DIR%
