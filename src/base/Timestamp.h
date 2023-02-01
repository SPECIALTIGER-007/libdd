#ifndef TIME_STAMP_H
#define TIME_STAMP_H

#include <sys/time.h>

#include <iostream>
#include <string>

namespace libdd {
class Timestamp {
public:
    Timestamp(): microSecondsSinceEpoch_(0) {}

    explicit Timestamp(int64_t microSecondsSinceEpoch)
        : microSecondsSinceEpoch_(microSecondsSinceEpoch) {}

    // 获取当前时间戳
    static Timestamp now();

    // 用std::string形式返回,格式[millisec].[microsec]
    //    [[nodiscard]] std::string toString() const;
    // 格式, "%4d年%02d月%02d日 星期%d %02d:%02d:%02d.%06d",时分秒.微秒
    [[nodiscard]] std::string toFormattedString(
            bool showMicroseconds = false) const;

    // 返回当前时间戳的微妙
    [[nodiscard]] int64_t microSecondsSinceEpoch() const {
        return microSecondsSinceEpoch_;
    }
    // 返回当前时间戳的秒数
    [[maybe_unused]] [[nodiscard]] time_t secondsSinceEpoch() const {
        return static_cast<time_t>(microSecondsSinceEpoch_ /
                                   kMicroSecondsPerSecond);
    }

    // 失效的时间戳，返回一个值为0的Timestamp
    [[maybe_unused]] static Timestamp invalid() {
        return {};
    }

    // 1秒=1000*1000微妙
    static const int kMicroSecondsPerSecond = 1000 * 1000;

private:
    // 表示时间戳的微秒数(自epoch开始经历的微妙数)
    int64_t microSecondsSinceEpoch_;
};

/**
 * 定时器需要比较时间戳，因此需要重载运算符
 */
inline bool operator<(Timestamp lhs, Timestamp rhs) {
    return lhs.microSecondsSinceEpoch() < rhs.microSecondsSinceEpoch();
}

inline bool operator==(Timestamp lhs, Timestamp rhs) {
    return lhs.microSecondsSinceEpoch() == rhs.microSecondsSinceEpoch();
}

// 如果是重复定时任务就会对此时间戳进行增加。
[[maybe_unused]] inline Timestamp addTime(Timestamp timestamp, double seconds) {
    // 将延时的秒数转换为微妙
    auto delta =
            static_cast<int64_t>(seconds * Timestamp::kMicroSecondsPerSecond);
    // 返回新增时后的时间戳
    return Timestamp(timestamp.microSecondsSinceEpoch() + delta);
}
} // namespace libdd


#endif // TIME_STAMP_H