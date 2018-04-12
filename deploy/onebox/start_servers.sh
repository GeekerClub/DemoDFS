#!/bin/bash
source env.sh

check_env_variable

if [ $? -ne 0 ]; then
    exit -1
fi

# build link for binary
echo -en $PRINT_GREEN"Prepare binary links ... "$PRINT_END
ln -sf $BLADE_ROOT_DIR/blade-bin/rsfs/rsfs_main
#ln -sf $BLADE_ROOT_DIR/rsfscli
echo -e $PRINT_RED"done"$PRINT_END

# kill all servers before restart them

# prepare flag parameters
gen_flag > $flag_file

# prepare common environment
add_dir $result_output_dir
add_dir $job_cache_dir

function StartMaster() {
    # start master server
    echo -en $PRINT_GREEN"Start master server ... "$PRINT_END
    for ((i = 0, port=$master_port, monitor_port=$master_monitor_port; \
          i < $master_number; ++i, ++port, ++monitor_port)); do
        echo -en $PRINT_GREEN#$i ".. "$PRINT_END 
        add_dir ${master_log}_$i
        add_dir ${master_working_dir}
        ./rsfs_main $args --rsfs_role=master \
            --rsfs_master_port=$port \
            --rsfs_master_monitor_port=$monitor_port \
            --log_dir=${master_log}_$i \
            --logtostderr &> master.$i.stderr &
    done
    sleep 3
    echo -e $PRINT_RED"done"$PRINT_END
}

function StartStemNode() {
    # start stemnode server
    echo -en $PRINT_GREEN"Start stemnode server ... "$PRINT_END
    for ((i = 0, port=$stemnode_port, monitor_port=$stem_monitor_port; \
          i < $stemnode_number; ++i, ++port, ++monitor_port)); do
        echo -en $PRINT_GREEN#$i ".. "$PRINT_END
        add_dir ${stemnode_log}_$i
        add_dir ${stemnode_working_dir}_$i
        ./rsfs_main $args --rsfs_role=stemnode \
            --rsfs_stemnode_port=$port \
            --rsfs_stemnode_monitor_port=$monitor_port \
            --log_dir=${stemnode_log}_$i \
            --logtostderr &> stemnode.$i.stderr &
    done
    echo -e $PRINT_RED"done"$PRINT_END
}

function StartLeafNode() {
    # start leafnode server
    echo -en $PRINT_GREEN"Start leafnode server ... "$PRINT_END
    for ((i = 0, port=$leafnode_port, monitor_port=$leaf_monitor_port; \
          i < $leafnode_number; ++i, ++port, ++monitor_port)); do
        echo -en $PRINT_GREEN#$i ".. "$PRINT_END
        add_dir ${leafnode_log}_$i
        add_dir ${leafnode_working_dir}_$i
        ./rsfs_main $args --rsfs_role=leafnode \
            --rsfs_leafnode_port=$port \
            --rsfs_leafnode_monitor_port=$monitor_port \
            --log_dir=${leafnode_log}_$i \
            --logtostderr &> leafnode.$i.stderr &
    done
    echo -e $PRINT_RED"done"$PRINT_END
}

function StartClientServer() {
    # start client server
    echo -en $PRINT_GREEN"Start client server ... "$PRINT_END
    for ((i = 0, port=$client_port, monitor_port=$client_monitor_port; \
          i < $client_number; ++i, ++port, ++monitor_port)); do
        echo -en $PRINT_GREEN#$i ".. "$PRINT_END
        add_dir ${client_log}_$i
        add_dir ${client_working_dir}_$i
        ./rsfs_main $args --rsfs_role=client \
            --rsfs_client_port=$port \
            --rsfs_client_monitor_port=$monitor_port \
            --rsfs_client_mode=server \
            --log_dir=${client_log}_$i \
            --logtostderr &> client.$i.stderr &
    done
    echo -e $PRINT_RED"done"$PRINT_END
}

function Start() {
    if [ x$1 == x"master" ]; then
        StartMaster
        sleep $start_sleep_time 
    elif [ x$1 == x"leaf" ]; then
        StartLeafNode
        sleep $start_sleep_time 
    elif [ x$1 == x"stem" ]; then
        StartStemNode
        sleep $start_sleep_time 
    elif [ x$1 == x"client" ]; then
        StartClientServer
        sleep $start_sleep_time 
    elif [ x$1 == x"all" ]; then
        StartMaster
        StartLeafNode
        StartStemNode
        StartClientServer
        sleep $start_sleep_time 
    else 
        echo -e "Usage: ./start_server.sh [all | master | stem | leaf | client]"
        echo -e "Example: ./start_server.sh stem leaf"
        echo -e "         ./start_server.sh master"
    fi
}

if [ $# -gt 0 ]; then
    for i in $@; do
        ./kill_servers.sh $i
        Start $i
    done
else 
    Start 
    exit;
fi

# all servers are started
echo -e $PRINT_RED"All servers are ready ... enjoy!"$PRINT_END
