#!/bin/bash
while true
do
	read -e -p "nexus> " cmd arg1 arg2
	case $cmd in
	"show")
		sh ./show_cluster.sh
	;;

	"stat")
		sh ./test_stat.sh
	;;

	"put")
		sh ./test_put.sh $arg1 $arg2
	;;

	"get")
		sh ./test_get.sh $arg1
	;;

	"getq")
		sh ./test_getq.sh $arg1
	;;

	"delete")
		sh ./test_del.sh $arg1
	;;
	"scan")
		sh ./test_scan.sh $arg1 $arg2
	;;
	"ls")
		sh ./test_scan.sh $arg1 $arg1"~"
	;;
	"watch")
		sh ./test_watch.sh $arg1 &
	;;
	"lock")
		sh ./test_lock.sh $arg1
	;;
	"login")
		sh ./test_log.sh $arg1 $arg2
	;;
	"register")
		sh ./test_register.sh $arg1 $arg2
	;;
	"whoami")
		sh ./test_whoami.sh
	;;
	"quit")
		exit 0
	;;

	*)
		echo "  show [ show cluster ]"
		echo "  stat [ show statistics ]"
		echo "  put (key) (value) [ update the data ] "
		echo "  get (key) [read the data by key ]"
		echo "  delete (key) [remove the data by key]"
		echo "  scan (start-key) (end-key) [scan from start-key to end-key(excluded)]"
		echo "  watch (key) [event will be triggered once value changed or deleted]"
		echo "  lock (key) [lock on specific key]"
		echo "  register (username) (password) [register a new user]"
		echo "  login (username) (password) [login and open a new session]"
		echo "  enter quit to exit shell"
	;;

	esac
done

