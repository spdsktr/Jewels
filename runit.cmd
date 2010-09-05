@echo off

call uploadit.cmd
plink -P 10022 root@localhost -pw "" "/media/cryptofs/apps/usr/palm/applications/com.jamesharris.jewelsfree/gemz"

