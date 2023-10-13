option = {
  legend: {},
  tooltip: {},
  dataset: {
    source: [
      ['', '1 threads', '2 threads', '4 threads', '8 threads'],
      ['easyloggingpp', 2663, 3077, 3520, 3601],
      ['fmtlog', 47.7, 28.9, 20.2, 13.9],
      ['glog', 3930, 4448, 5536, 7914],
      ['haclog', 113, 72.4, 78.0, 1583],
      ['loguru', 2281, 4153, 3585, 3392],
      ['nanolog', 177, 260, 273, 328],
      ['quill_bounded', 56.5, 33.3, 20.2, 13.0],
      ['spdlog_async', 632, 1128, 1858, 2589],
      ['spdlog_async', 498, 923, 960, 1289],
    ]
  },
  xAxis: { type: 'category' },
  yAxis: {},
  // Declare several bar series, each will be mapped
  // to a column of dataset.source by default.
  series: [{ type: 'bar' }, { type: 'bar' }, { type: 'bar' }, { type: 'bar' }]
};