# Buddy 伙伴算法

## 1. 简介

Buddy 算法是一种常见的内存分配算法。该算法的优点是可以有效地利用内存空间，避免了内存碎片的产生。但是，它也有一些缺点，例如内存池的大小应当为 2 的幂，否则会浪费一些内存空间。此外，Buddy 算法容易产生内部碎片。

在本次作业中，你需要实现一个简单的 Buddy 算法并且通过测试。

## 2. 实现要求

本作业中约定最小的分配单位是大小为 $4K$ 的页（页面 / page），其 $rank=1$（页的大小为 $4K \times 2^{rank-1}$）。

你需要完成 `buddy.c` 中的内容，需要实现的函数及说明如下：

> 合法的 $rank = 1,2, ..., 16$
>
> `OK`, `EINVAL`, `ENOSPC` 等其他定义详见 `buddy.h`

1. `int init_page(void *p, int pgcount)`：初始化页面

   - 你需要管理 `pgcount` 个 $4K$ 页，这些 $4K$ 页连续分配并且起始地址是 `p`
2. `void *alloc_pages(int rank)`：分配一个指定 $rank$ 的页面
   - 返回值为分配页的起始地址

   - 若无足够空间则返回 `-ENOSPC`
   - 若传入的 `rank` 非法，返回 `-EINVAL`
3. `int return_pages(void *p)`：释放一个页至 buddy 系统
   - 合法的 `p` 是尚未释放的 `alloc_pages` 返回的页地址
   - 若释放成功，返回 `OK`
   - 若传入的页地址非法则返回 `-EINVAL`
4. `int query_ranks(void *p)`：查询一个页面的 rank
   - 未被分配的页面按照其最大的 rank 进行查询
   - 若传入的页地址非法则返回 `-EINVAL`
5. `int query_page_counts(int rank)`：指定 rank 查询剩余多少未分配的页，如果传递的 rank 非法，返回 `-EINVAL`

你需要确保你的分配算法可以通过测试并输出。最终测试通过比对输出进行评分。  