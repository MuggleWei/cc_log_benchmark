option = {
  legend: {},
  tooltip: {},
  dataset: {
    source: [
      ['', '1 threads', '6 threads', '12 threads', '24 threads'],
      ['easyloggingpp', 3875, 3155, 3053, 2915],
      ['fmtlog', 94.2, 62.9, 45.3, 36.7],
      ['glog', 6710, 6099, 8952, 9298],
      ['haclog', 177, 29.9, 30.9, 16.7],
      ['loguru', 3090, 3862, 6333, 6304],
      ['nanolog', 104, 21.0, 11.5, 6.69],
      ['quill_bounded', 111, 998, 1165, 1165],
      ['quill_unbounded', 70.0, 462, 686, 675],
      ['reckless', 442, 463, 438, 390],
      ['spdlog_async', 820, 2413, 2527, 2483],
      ['spdlog_sync', 747, 1146, 1384, 1454],
    ]
  },
  xAxis: { type: 'category' },
  yAxis: {},
  // Declare several bar series, each will be mapped
  // to a column of dataset.source by default.
  series: [{ type: 'bar' }, { type: 'bar' }, { type: 'bar' }, { type: 'bar' }]
};