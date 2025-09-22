#include "MT.h"
#include "FileStats.h"

#include <iostream>
#include <syncstream>

struct Task {
    std::filesystem::path file_path;
    bool should_stop;
};

class TaskQueue {
public:
    void push(Task task) {
        std::lock_guard q_lock(mutex);
        tasks.push(task);
        has_tasks.notify_one();
    }
    void push_end() {
        std::lock_guard q_lock(mutex);
        tasks.push({ {}, true });
        has_tasks.notify_one();
    }
    Task pop() {
        std::unique_lock q_lock(mutex);
        has_tasks.wait(q_lock);
        Task task = tasks.front();
        tasks.pop();
        return task;
    }

private:
    std::queue<Task> tasks;
    std::condition_variable has_tasks;
    std::mutex mutex;
};

ThreadPool::ThreadPool(size_t n_threads) {
    total = FileStats::valid("total");
    task_queue = std::make_unique<TaskQueue>();

    for (size_t i = 0; i < n_threads; ++i) {
        threads.push_back(std::jthread([this] {
            worker();
        }));
    }
}

ThreadPool::~ThreadPool() {
    wait_for_all();
}

void ThreadPool::enqueue_file(const std::filesystem::path &path) {
    task_queue->push(Task { path, false });
}

void ThreadPool::wait_for_all() {
    for (int i = 0; i < threads.size(); i++) task_queue->push_end();
    for (auto &t : threads) if (t.joinable()) t.join();
}

void ThreadPool::worker() {
    while (true) {
        auto task = task_queue->pop();
        if (task.should_stop) return;

        FileStats stats = get_file_stats(task.file_path);

        std::osyncstream(std::cout) << task.file_path
            << ": total=" << stats.total_lines << ", blank=" << stats.blank_lines
            << ", code=" << stats.code_lines << ", comment=" << stats.comment_lines
            << std::endl;

        std::lock_guard t_lock(total_mutex);
        total.code_lines += stats.code_lines;
        total.blank_lines += stats.blank_lines;
        total.total_lines += stats.total_lines;
        total.comment_lines += stats.comment_lines;
    }
}

FileStats ThreadPool::get_total() {
    std::lock_guard t_lock(total_mutex);
    return total;
}
