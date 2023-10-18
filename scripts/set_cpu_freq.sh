#!/bin/bash

# # set governor
# sudo cpupower frequency-set --governor userspace
# 
# # set maximum and minmum frequency
# sudo cpupower frequency-set --max 4GHz --min 1GHz
# 
# # lock frequency to 2GHz
# sudo cpupower frequency-set --freq 2GHz

# set frequency performance
sudo cpupower frequency-set -g performance

# with turbo boost enable, set max and min immediately
sudo cpupower frequency-set --max 3.2GHz --min 3.2GHz

# verify settings
sudo cpupower frequency-info
