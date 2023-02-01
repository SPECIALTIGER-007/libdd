//
// Created by tiger on 2/1/23.
//

#ifndef LIBDD_NONCOPYABLE_H
#define LIBDD_NONCOPYABLE_H

namespace libdd {
class noncopyable {
public:
    noncopyable(noncopyable &) = delete;
    noncopyable &operator=(noncopyable &) = delete;

protected:
    noncopyable() = default;
    ~noncopyable() = default;
};

} // namespace libdd

#endif // LIBDD_NONCOPYABLE_H
