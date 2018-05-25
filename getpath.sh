#!bin/bash

NODE="lovelace"

while [ "$#" -gt 0 ] ; do
	case $1 in
		-n)
			shift
			NODE="$1"
			;;
		*)
			shift
			;;
	esac
done

NODE=$(echo "$NODE" | tr '[:upper:]' '[:lower:]')

if [ $NODE == "bellman-ford" ]
	$(mtr 127.0.0.1 --report --no-dns)
fi 

if [ $NODE == "lovelace" ]
	$(mtr 10.10.4.1 --report --no-dns)
fi

if [ $NODE == "knuth" ]
	$(mtr 10.10.8.2 --report --no-dns)
fi 

if [ $NODE == "hopper" ]
	$(mtr 10.10.2.1 --report --no-dns)
fi 

if [ $NODE == "cerf" ]
	$(mtr 10.10.1.1 --report --no-dns)
fi 

if [ $NODE == "baran" ]
	$(mtr 10.10.5.2 --report --no-dns)
fi 

exit 0;