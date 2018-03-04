#include <algorithm>
#include <iostream>
#include <iterator>
#include <functional>

template <class It, class Out, class Compare = std::less<int>>
Out merge(It first1, It last1, It first2, It last2, Out out, Compare cmp = Compare{})
{
    while (first1 != last1)
    {
        if (first2 == last2)
            return std::copy(first1, last1, out);
        if (cmp(*first2, *first1))
        {
            *out = *first2;
            ++first2;
        }
        else
        {
            *out = *first1;
            ++first1;
        }
        ++out;
    }
    return std::copy(first2, last2, out);
}
template <class It, class Compare = std::less<int>>
void merge_sort(It first, It last, Compare cmp = Compare{})
{
    if (std::distance(first, last) <= 1)
        return;
    auto const middle = std::next(first, std::distance(first, last) / 2);
    merge_sort(first, middle, cmp);
    merge_sort(middle, last, cmp);
    std::inplace_merge(first, middle, last, cmp);
}

template <class It, class Compare = std::less<int>>
void shiftDown(It first, int head, int bottom, Compare cmp = Compare{})
{
    int inner = 0;
    int flag = 1;
    while ((head * 2 <= bottom) && flag)
    {
        if (head * 2 == bottom)
            inner = head * 2;
        else if (cmp(*(first + head * 2), *(first + head * 2 + 1)))
            inner = head * 2;
        else
            inner = head * 2 + 1;
        if (cmp(*(first + head), *(first + inner)))
        {
            std::iter_swap(first + head, first + inner);
            head = inner;
        }
        else
            flag = 0;
    }
}

template <class It, class Compare = std::less<int>>
void heap_sort(It first, It last, Compare cmp = Compare{})
{
    for (int i = (std::distance(first, last) / 2) - 1; i >= 0; --i)
        shiftDown(first, i, std::distance(first, last));
    for (int i = std::distance(first, last) - 1; i >= 1; --i)
    {
        std::iter_swap(first, first + i);
        shiftDown(first, 0, i - 1);
    }
}
template <class It, class Compare = std::less<int>>
void quick_sort(It first, It last, Compare cmp = Compare{})
{
    if (std::distance(first, last) <= 1)
        return;
    auto const middle = std::next(first, std::distance(first, last) / 2);
    std::nth_element(first, middle, last, cmp);
    quick_sort(first, middle, cmp);
    quick_sort(middle, last, cmp);
}
template <class It, class Compare = std::less<int>>
void insertion_sort(It first, It last, Compare cmp = Compare{})
{
    if (!(first < last))
        return;
    for (It i = first + 1; i != last; ++i)
        for (It j = i; j != first && *j < *(j - 1); --j)
            std::iter_swap(j - 1, j);
}
