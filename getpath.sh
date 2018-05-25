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
# mtr some.ip.address.yo --report --no-dns
fi 

if [ $NODE == "lovelace" ]

# mtr some.ip.address.yo --report --no-dns

fi

if [ $NODE == "knuth" ]
# mtr some.ip.address.yo --report --no-dns
fi 

if [ $NODE == "hopper" ]
# mtr some.ip.address.yo --report --no-dns
fi 

if [ $NODE == "cerf" ]
# mtr some.ip.address.yo --report --no-dns
fi 

if [ $NODE == "baran" ]
# mtr some.ip.address.yo --report --no-dns
fi 

exit 0;