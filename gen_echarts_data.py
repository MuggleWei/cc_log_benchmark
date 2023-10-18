import os
import sys


def parse_num(line, head_end):
    """
    parse number and unit
    """
    num_begin = 0
    for i in range(len(line[head_end:])):
        if line[head_end:][i] == " ":
            continue
        num_begin = i + head_end
        break

    num_end = num_begin
    for i in range(len(line[num_begin:])):
        if line[num_begin:][i] == " ":
            num_end = i + num_begin
            break
    num = line[num_begin:num_end]

    unit_begin = num_end + 1
    unit_end = unit_begin
    for i in range(len(line[unit_begin:])):
        if line[unit_begin:][i] == " ":
            unit_end = i + unit_begin
            break
    unit = line[unit_begin:unit_end]

    if unit == "ns":
        pass
    elif unit == "us":
        num = str(float(num) * 1000)
    elif unit == "ms":
        num = str(float(num) * 1000000)
    return num


def parse_benchmark_info(filepath):
    """
    parse benchmark report
    """
    info = {
        "min_time": {},
        "iter_repeat": {},
    }
    with open(filepath, "r") as f:
        for line in f:
            if line.find("Fixture") <= 0:
                continue
            head_end = line.find(" ")
            head = line[:head_end]
            head_v = head.split("/")

            num = parse_num(line, head_end)

            if len(head_v) == 4:
                # min_time
                thread_num = head_v[-1].split(":")[-1]
                info["min_time"][thread_num] = num
            elif len(head_v) == 5:
                if not head_v[-1].endswith("_median"):
                    continue
                thread_num = head_v[-1].split(":")[-1].split("_")[0]
                info["iter_repeat"][thread_num] = num
    return info


def get_benchmark_files(target_dir):
    """
    get benchmark file dict
    """
    benchmark_file_dict = {}
    files = os.listdir(target_dir)
    for filename in files:
        filepath = os.path.join(target_dir, filename)
        if os.path.isdir(filepath):
            continue
        if not filename.startswith("benchmark_"):
            continue
        if not filename.endswith(".txt"):
            continue
        name = filename[len("benchmark_"):].split(".")[0]
        benchmark_file_dict[name] = filepath
    return benchmark_file_dict


def get_bar_data(num_threads, info_dict):
    """
    get bar data
    """
    datas = []
    for num_thread in num_threads:
        if num_thread not in info_dict:
            break
        datas.append(info_dict[num_thread])
    return datas


if __name__ == "__main__":
    target_dir = "build"
    if len(sys.argv) == 2:
        target_dir = sys.argv[1]

    # get benchmark files
    benchmark_file_dict = get_benchmark_files(target_dir)

    # get benchmark infos
    benchmark_info = {}
    for name, filepath in benchmark_file_dict.items():
        benchmark_info[name] = parse_benchmark_info(filepath)

    # get threads info
    min_time_threads = []
    iter_repeat_threads = []
    for name, info in benchmark_info.items():
        min_time = info["min_time"]
        for num_thread, v in min_time.items():
            if num_thread not in min_time_threads:
                min_time_threads.append(num_thread)

        iter_repeat = info["iter_repeat"]
        for num_thread, v in iter_repeat.items():
            if num_thread not in iter_repeat_threads:
                iter_repeat_threads.append(num_thread)

    # output min time
    print("--------------------------------")
    print("min_time")
    print("--------------------------------")
    print("['','{}'],".format("','".join(min_time_threads)))
    for name in sorted(benchmark_info.keys()):
        info = benchmark_info[name]
        datas = get_bar_data(min_time_threads, info["min_time"])
        if len(datas) > 0:
            print("['{}',{}],".format(name, ",".join(datas)))
    print("")

    # output iter repeat
    print("--------------------------------")
    print("iter_repeat")
    print("--------------------------------")
    print("['','{}'],".format("','".join(iter_repeat_threads)))
    for name in sorted(benchmark_info.keys()):
        info = benchmark_info[name]
        datas = get_bar_data(iter_repeat_threads, info["iter_repeat"])
        if len(datas) > 0:
            print("['{}',{}],".format(name, ",".join(datas)))
