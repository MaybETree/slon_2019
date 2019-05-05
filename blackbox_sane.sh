#!/bin/bash

# Loop from -10 to 10
for i in $(seq -10 10)
do
	# write x coord to output
	# /dev/pts/15 is a different terminal window
	# so the output from the commands doesn't mix with
	# the actual output
	echo -ne $i"\t" > /dev/pts/15

	# start TOR and redirect all output to a ramfile
	tor &>/tmp/tor_monitor &

	# wait until the symbols "100%" appear in the monitor file.
	# this means that TOR is fully initialised
	while :
	do
		cat /tmp/tor_monitor | grep "100%" && break
	done

	
	# send request to blackbox via TOR
	curl -s --socks5-hostname 127.0.0.1:9050 \
		-L -X POST http://95.85.18.95:8010/blackbox \
		-d value=$i  |
			# regex to extract output from blackbox
			grep -o -P -e 'value="-?\d+\.?\d*"' |
			# regex to strip junk characters
			# and then write to console
			grep -o -P -e '-?\d+\.?\d*' >\
			/dev/pts/15

	# stop tor, so the next iteration we'll
	# have a differetent IP address
	killall tor
done
