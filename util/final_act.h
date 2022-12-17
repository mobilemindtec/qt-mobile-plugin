#ifndef FINAL_ATC_H
#define FINAL_ATC_H

#include <utility>

template <class F>
class final_act
{
public:
    explicit final_act(F f) noexcept
      : f_(std::move(f)), invoke_(true) {}

    final_act(final_act&& other) noexcept
     : f_(std::move(other.f_)),
       invoke_(other.invoke_)
    {
        other.invoke_ = false;
    }

    final_act(const final_act&) = delete;
    final_act& operator=(const final_act&) = delete;

    ~final_act() noexcept
    {
        if (invoke_) f_();
    }

private:
    F f_;
    bool invoke_;
};


#endif // FINAL_ATC_H
