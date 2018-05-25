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

if [ "$NODE" == "bellman-ford" ];
then
	$(mtr 127.0.0.1 --report --no-dns)
fi

if [ "$NODE" == "lovelace" ];
then
	$(mtr 10.10.4.1 --report --no-dns)
fi

if [ "$NODE" == "knuth" ];
then
	$(mtr 10.10.8.2 --report --no-dns)
fi

if [ "$NODE" == "hopper" ];
then
	$(mtr 10.10.2.1 --report --no-dns)
fi

if [ "$NODE" == "cerf" ];
then
	$(mtr 10.10.1.1 --report --no-dns)
fi

if [ "$NODE" == "baran" ];
then
	$(mtr 10.10.5.2 --report --no-dns)
fi

exit 0