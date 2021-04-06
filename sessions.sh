#!/bin/bash
IMAGE_NAME="esp-hmi"
IMAGE_VERSION="1.0.0"

WORK_PATH=$(cd $(dirname $0); pwd)
echo "WORK_PATH: ${WORK_PATH}"

export PROJECTS_PATH=${WORK_PATH}/projects

session=${IMAGE_NAME}

tmux has-session -t $session >/dev/null 2>&1
if [ $? = 0 ];then
    tmux attach-session -t $session
    exit
fi

tmux new-session -d -s $session -n $session
tmux split-window -t $session:0 -h
tmux split-window -t $session:0.0 -v

tmux send-keys -t $session:0.0 'cd ${PROJECTS_PATH};/bin/bash ${PROJECTS_PATH}/hmi_sim.sh' C-m
tmux send-keys -t $session:0.1 'cd ${PROJECTS_PATH};Gui-Guider' C-m
tmux send-keys -t $session:0.2 'cd ${PROJECTS_PATH};source ${IDF_PATH}/export.sh;/bin/bash ${PROJECTS_PATH}/hmi.sh' C-m

tmux select-pane -t $session:0.1
tmux attach-session -t $session