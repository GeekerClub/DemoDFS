#!/bin/bash

function KillMaster() {
    for i in $(ps -ef | grep "rsfs_main" \
        | grep "master" | grep -v "grep " | awk '{print $2}'); do

        echo "Shutdown server at pid :$i"
        kill -9 $i
    done
}

function KillStemNode() {
    for i in $(ps -ef | grep "rsfs_main" | grep "stemnode"\
        | grep -v "grep " | awk '{print $2}'); do

        echo "Shutdown server at pid :$i"
        kill -9 $i
    done
}

function KillLeafNode() {
    for i in $(ps -ef | grep "rsfs_main" | grep "leafnode"\
        | grep -v "grep " | awk '{print $2}'); do

        echo "Shutdown server at pid :$i"
        kill -9 $i
    done
}

function KillClientServer() {
    for i in $(ps -ef | grep "rsfs_main" | grep "client"\
        | grep -v "grep " | awk '{print $2}'); do

        echo "Shutdown server at pid :$i"
        kill -9 $i
    done
}


if [ x$1 == x"master" ]; then
    KillMaster
elif [ x$1 == x"leaf" ]; then
    KillLeafNode
elif [ x$1 == x"stem" ]; then
    KillStemNode
elif [ x$1 == x"client" ]; then
    KillClientServer
elif [ x$1 == x"all" ]; then
    KillMaster
    KillLeafNode
    KillStemNode
    KillClientServer
else 
    echo -e "Usage: ./kill_server.sh [all | master | stem | leaf | client]"
    echo -e "Example: ./kill_server.sh stem leaf"
    echo -e "         ./kill_server.sh master"
fi

