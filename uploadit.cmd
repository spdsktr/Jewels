@echo off

plink -P 10022 root@localhost -pw "" "killall -9 gdbserver gemz"
pscp -scp -P 10022 -pw "" gemz root@localhost:/media/cryptofs/apps/usr/palm/applications/com.jamesharris.jewelsfree
