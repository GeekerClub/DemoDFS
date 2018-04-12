
#### identity ####
user=$USER
role=$USER

#### print environment ####
PRINT_GREEN='\033[40;32m'
PRINT_YELLOW='\033[40;33m'
PRINT_WHITE='\033[40;37m'
PRINT_RED='\033[40;31m'
PRINT_END='\033[0m'

#### server setting ####
#ip=127.0.0.1
local_ip=`/sbin/ifconfig  | grep 'inet addr:'| grep -v '127.0.0.1' | cut -d: -f2 | awk '{ print $1}'`
ip=$local_ip
start_sleep_time=3
client_port=10000
master_port=11000
stemnode_port=22000
leafnode_port=23000
client_monitor_port=8010
master_monitor_port=8110
leaf_monitor_port=8210
stem_monitor_port=8310
flag_file=./rsfs.flag

leafnode_number=6
stemnode_number=2
client_number=1

#### log setting ####
v=20
master_log=master_log
stemnode_log=stemnode_log
leafnode_log=leafnode_log
client_log=client_log
master_working_dir=master_data
stemnode_working_dir=stemnode_data
leafnode_working_dir=leafnode_data
client_working_dir=client_data
master_number=1

#### output setting ####
result_output_dir=result_output/
job_cache_dir=job_cache/

#### help function ####

function add_dir() {
    if [ -d $1 ]; then
        return 0
    fi
    mkdir $1
}

function gen_flag() {
    echo --rsfs_master_addr=$ip
    echo --rsfs_master_port=$master_port
    echo --rsfs_query_output_dir=$result_output_dir
    echo --rsfs_job_cache_dir=$job_cache_dir
    echo --rsfs_remove_job_waiting_time=10000
    echo --v=25
    echo --log_dir=./
}

#### prepare configuration ####
#gen_flag > $flag_file
args=--flagfile=$flag_file

function _find_project_root()
{
    local dir
    dir=$PWD;
    while [ "$dir" != "/" ]; do
        if [ -f "$dir/BLADE_ROOT" ]; then
            echo "$dir"
            return 0
        fi;
        dir=`dirname "$dir"`
    done
    return 1
}

BLADE_ROOT_DIR=`_find_project_root`

#### check environment variable ####
function check_env_variable() {
    if [ x$JAVA_HOME = "x" ]; then
        echo -e $PRINT_YELLOW"JAVA_HOME is not set, access hdfs is not allow!!!"$PRINT_END
    elif [ x$CLASSPATH = "x" ]; then
        echo -e $PRINT_YELLOW"CLASSPATH is not set, access hdfs is not allow!!!"$PRINT_END
    elif [ x$LD_LIBRARY_PATH = "x" ]; then
        echo -e $PRINT_YELLOW"LD_LIBRARY_PATH is not set, access hdfs is not allow!!!"$PRINT_END
    fi
    split_path=$(echo $LD_LIBRARY_PATH | awk -F':' '{for(i=1;i<=NF;i++){print $i}}')
    valid_path=''
    for i in $split_path; do
        if [ -d $i -a x$valid_path = "x" ]; then
            valid_path=$i
        elif [ -d $i ]; then
            valid_path=$valid_path:$i
        fi
    done
    if [ x$valid_path = "x" ]; then
        exit -1
    fi
    num=$(echo $valid_path | awk -F':' '{for(i=1;i<=NF;i++){print $i}}' \
        | xargs -i find {} -maxdepth 1 -name libjvm.so | wc -l)
    if [ $num -eq 0 ]; then
        project_root=$(_find_project_root)
        jvm_paths=$(find $project_root -name libjvm.so)
        jvm_path=$(echo $jvm_paths | awk '{print $1}')
        if [ "x$jvm_paths" = 'x' ]; then
            echo -e $PRINT_YELLOW"libjvm.so is not set, program cannot run!!!"$PRINT_END
            echo -e $PRINT_YELLOW"download lastest hadoop client"$PRINT_END
            echo -e $PRINT_YELLOW"export libjvm.so to runtime path"$PRINT_END
            exit -1
        fi
        echo -e $PRINT_GREEN"add libjvm.so to LD_LIBRARY_PATH"$PRINT_END
        export LD_LIBRARY_PATH=$(dirname $jvm_path):$LD_LIBRARY_PATH
    else
        jvm_paths=$(echo $valid_path | awk -F':' '{for(i=1;i<=NF;i++){print $i}}' \
            | xargs -i find {} -maxdepth 1 -name libjvm.so)
        jvm_path=$(echo $jvm_paths | head -n 1)
        echo -e $PRINT_GREEN"add libjvm.so to LD_LIBRARY_PATH"$PRINT_END
        export LD_LIBRARY_PATH=$(dirname $jvm_path):$LD_LIBRARY_PATH
    fi
}

