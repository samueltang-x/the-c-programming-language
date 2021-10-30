#!/bin/bash

set -o errexit -o noclobber -o nounset -o pipefail
shopt -s expand_aliases

log_level=${2:-INFO}

logger=$(dirname $(realpath $0))/utils/logger.sh

source $logger
alias ERROR='logger ERROR'
alias WARNING='logger WARNING'
alias INFO='logger INFO'
alias DEBUG='logger DEBUG'

__logging_level=${log_level^^}
#__logging_level='DEBUG'
# Redirect output to std out, instead of log file
__redirect_to_standard_out=TRUE
# Set time format like: 2016-10-19 17:57:00.372
__logger_time_format='%F %T.%3N'

logger DEBUG "logger module loaded."


function test() {

    local target_file=$(find test/ -name test-${1}.c)
    if [[ -z $target_file ]]; then
        ERROR "test file not found: test-${1}.c"
        exit 1;
    fi
    local test_dir=$(dirname $target_file)
    local test_folder=$(basename $test_dir)
    local test_dir=$(dirname $test_dir)
    local root_dir=$(dirname $test_dir)
    local src_dir=${root_dir}/src
    local build_dir=${root_dir}/build/${test_folder}

    [ -d $build_dir ] || mkdir  -pv $build_dir

    local output_file=${build_dir}/${1}

    DEBUG "compiling $target_file ..."
    gcc \
        ${target_file} \
        -o ${output_file}

    INFO "executing test: ${output_file} ..."
    local ns_start=$(date '+%s%N')
    ${output_file}
    local ns_end=$(date '+%s%N')
    local run_time=$(echo "scale=9; (${ns_end} - ${ns_start}) / 1000000000" | bc)
    INFO "finished test ${output_file}, run time: ${run_time} s, exit code: $?"
}

test $1
