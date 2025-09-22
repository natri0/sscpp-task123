#pragma once

#include <queue>
#include <condition_variable>
#include <mutex>
#include <thread>
#include <filesystem>
#include <memory>

#include "FileStats.h"

class TaskQueue;

class ThreadPool {
public:
    ThreadPool(size_t n_threads);
    ~ThreadPool();

    void enqueue_file(const std::filesystem::path &path);

    void wait_for_all();
    FileStats get_total();
private:
    std::unique_ptr<TaskQueue> task_queue;
    std::vector<std::jthread> threads;

    std::mutex total_mutex;
    FileStats total;

    void worker();
};
