#!/bin/bash

for i in $(seq -10 10);  do echo -ne $i"\t" > /dev/pts/2; tor &>/tmp/tor_monitor & while : ;do cat /tmp/tor_monitor | grep "100%" && break; done; curl -s --socks5-hostname 127.0.0.1:9050 -L -X POST http://95.85.18.95:8010/blackbox -d value=$i  | grep -o -P -e 'value="-?\d+\.?\d*"' |  grep -o -P -e '-?\d+\.?\d*' > /dev/pts/2; killall tor; done
