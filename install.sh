#!/bin/bash
rm duipai install.log 2>&-
bash src/install.sh >>install.log 2>&1
if [ -e duipai ]; then
    echo -e "\033[32;1mOK\033[0m"
    rm install.log
else
    echo -e "\033[31;1mFAIL\033[0m"
fi
