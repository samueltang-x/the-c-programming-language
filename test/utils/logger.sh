#############################################################################
# Function: A shell function to logging
# Initail:  V-0.0.1     Mar/05/2016
# Revision: V-1.0.0     Sep/22/2016
# Revision: V-1.0.2     Oct/20/2016
#                       Added case insensitive support of event level and logging level setting.
# Revision: V-1.0.3     Mar/26/2017
#                       Changed the method for converting strings to uppercase,
#                           so that it can works well in bash versions elder than 4.0.
# Author:   EXANTNG/xiangyuan.tang@ericsson.com, samuel.x.tang@gmail.com
#
# Parameters can be set from caller during initializing this logger:
#           __logger_log_file, __logging_level, __logger_time_format, __redirect_to_standard_out.
#
#           __logger_log_file=<log-file-name>
#           __logging_level={ ERROR | WARNING | INFO | DEBUG }
#           __logger_time_format=<FORMAT>
#           __redirect_to_standard_out={ TRUE | FALSE }
#
#   Note:   (1) Setting __redirect_to_standard_out to TRUE will shadow __logger_log_file parameter,
#           (2) The FORMAT of __logger_time_format is same as linux built-in data command, but with beginning + removed.
#           (3) __logger_log_file and __logger_time_format can be updated in runtime by calling logger() function.
#############################################################################


function logger()
{
    # Usage: logger [event_level [log_message [log_file [time_format]]]]
    local caller=$0
    local event_level=${1:-INFO}
    local log_message=${2:-' '}
    local default_log_file="${caller%.*}.log"
    local log_file="${3:-${default_log_file}}"
    local time_format=${4:-%F %T.%4N}
    local rediret_to_standard_out=${__redirect_to_standard_out:=FALSE}
    local logging_level=${__logging_level:=INFO}
    log_file=${__logger_log_file:=${log_file}}
    time_format=${__logger_time_format:=${time_format}}

    local log_time=$(date +"$time_format")
    local field_separator=' '

    # Convert to uppercase.
    # Updated in version V-1.0.3
    event_level=${event_level^^}
    logging_level=${logging_level^^}
    rediret_to_standard_out=${rediret_to_standard_out^^}
    # event_level=$(echo -ne "${event_level}" | awk '{print toupper($0)}')
    # logging_level=$(echo -ne "${logging_level}" | awk '{print toupper($0)}')
    # rediret_to_standard_out=$(echo -ne "${rediret_to_standard_out}" | awk '{print toupper($0)}')

    # Map level strings to relevant numbers.
    logging_level_index=$(echo -e "ERROR:40\nWARNING:30\nINFO:20\nDEBUG:10" | grep ${logging_level} | cut -d':' -f2)
    event_level_index=$(echo -e "ERROR:40\nWARNING:30\nINFO:20\nDEBUG:10" | grep ${event_level} | cut -d':' -f2)

    # Set font color to Red for ERROR and WARNING events.
    if [ "X${event_level}" == "XERROR" -o "X${event_level}" == "XWARNING" ]
    then
        event_level="\e[31m${event_level}\e[0m"
    fi

    if [ ${event_level_index} -ge ${logging_level_index} ]
    then
        if [ $rediret_to_standard_out != 'TRUE' ]
        then
            echo -e "${log_time}${field_separator}[${event_level}]${field_separator}${log_message}" >> ${log_file}
        else
            echo -e "${log_time}${field_separator}[${event_level}]${field_separator}${log_message}"
        fi
    fi
}

