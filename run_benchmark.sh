#!/bin/bash

origin_dir="$(dirname "$(readlink -f "$0")")"
build_dir=$origin_dir/build

if [ ! -d $build_dir ]; then
	echo "build directory not exists!"
	exit 1
fi

cd $build_dir

echo "generate random data"
./bin/gen_random_data

run_benchmark() {
	local name=$1
	./bin/gbenchmark_$name 2>&1 | tee benchmark_$name.txt

	echo "sleep for a while, wait CPU temperature drops"
	sleep 15
}

run_benchmark easyloggingpp
run_benchmark fmtlog_drop
run_benchmark fmtlog_block
run_benchmark glog
run_benchmark haclog
run_benchmark loguru
run_benchmark nanolog
run_benchmark quill_bounded_blocking
run_benchmark quill_bounded_dropping
run_benchmark reckless
run_benchmark spdlog_async
run_benchmark spdlog_sync
