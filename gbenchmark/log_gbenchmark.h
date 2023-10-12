#ifndef LOG_GBENCHMARK_H_
#define LOG_GBENCHMARK_H_

#define ITER_COUNT 10000
#define REPEAT_COUNT 5
#define MIN_TIME 3.0

#define RUN_GBENCHMARK(fixture, name)                                          \
  /* min time */                                                               \
  BENCHMARK_REGISTER_F(fixture, name)->Threads(1)->MinTime(MIN_TIME);          \
  BENCHMARK_REGISTER_F(fixture, name)->Threads(2)->MinTime(MIN_TIME);          \
  BENCHMARK_REGISTER_F(fixture, name)->Threads(4)->MinTime(MIN_TIME);          \
  /* iteration * repeat */                                                     \
  BENCHMARK_REGISTER_F(fixture, name)                                          \
      ->Threads(1)                                                             \
      ->Iterations(ITER_COUNT)                                                 \
      ->Repetitions(REPEAT_COUNT);                                             \
  BENCHMARK_REGISTER_F(fixture, name)                                          \
      ->Threads((std::thread::hardware_concurrency() / 2) > 0                  \
                    ? (std::thread::hardware_concurrency() / 2)                \
                    : 1)                                                       \
      ->Iterations(ITER_COUNT)                                                 \
      ->Repetitions(REPEAT_COUNT);                                             \
  BENCHMARK_REGISTER_F(fixture, name)                                          \
      ->Threads(std::thread::hardware_concurrency())                           \
      ->Iterations(ITER_COUNT)                                                 \
      ->Repetitions(REPEAT_COUNT);                                             \
  BENCHMARK_REGISTER_F(fixture, name)                                          \
      ->Threads(std::thread::hardware_concurrency() * 2)                       \
      ->Iterations(ITER_COUNT)                                                 \
      ->Repetitions(REPEAT_COUNT);                                             \
  /* gbenchmark main*/                                                         \
  BENCHMARK_MAIN();

#endif // !LOG_GBENCHMARK_H_