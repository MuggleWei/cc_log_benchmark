#!/bin/bash

echo "----------------"
echo "cpu info min freq"
cat /sys/devices/system/cpu/cpu*/cpufreq/cpuinfo_min_freq

echo "----------------"
echo "cpu info max freq"
cat /sys/devices/system/cpu/cpu*/cpufreq/cpuinfo_max_freq

echo "----------------"
echo "cpu scaling_min_freq"
cat /sys/devices/system/cpu/cpu*/cpufreq/scaling_min_freq

echo "----------------"
echo "cpu scaling_max_freq"
cat /sys/devices/system/cpu/cpu*/cpufreq/scaling_max_freq

echo "----------------"
echo "try to lock cpu min freq"
echo 3200000 | sudo tee /sys/devices/system/cpu/cpu*/cpufreq/scaling_min_freq

echo "----------------"
echo "try to lock cpu max freq"
echo 3200000 | sudo tee /sys/devices/system/cpu/cpu*/cpufreq/scaling_max_freq

echo "----------------"
echo "cpu scaling_cur_freq"
cat /sys/devices/system/cpu/cpu*/cpufreq/scaling_cur_freq
