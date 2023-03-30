# Buddy 伙伴算法

## 1. 简介

Buddy 算法是一种常见的内存分配算法。该算法的优点是可以有效地利用内存空间，避免了内存碎片的产生。但是，它也有一些缺点，例如内存池的大小最好是 2 的幂次方，否则会浪费一些内存空间。此外， Buddy 算法容易产生内部碎片。在本次作业中，你需要实现一个简单的 Buddy 算法并且通过测试。  

## 2. 实现要求

本作业中约定最小的分配单位是 4K（rank=1）页。

本次作业你需要实现至少以下函数：

1. `int init_page(void *p, int pgcount)`：初始化 buddy 页面。你需要管理 `pgcount` 个 4K 页，这些 4K 页连续分配并且起始地址是 `p`
2. `void *alloc_pages(int rank)`：分配一个给定 rank 的页面，返回这个页的地址。如果没有足够空间则返回 `-ENOSPC`。如果传递的 rank 非法，返回 `-EINVAL`
3. `int return_pages(void *p)`：归还一个页给 buddy 系统。如果正常归还返回 `OK`，如果传递的页地址非法则返回 `-EINVAL`
4. `int query_ranks(void *p)`：查询一个页面的 rank，如果传递的页地址非法则返回 `-EINVAL`。未被分配的页面按照其最大的 rank 进行查询
5. `int query_page_counts(int rank)`：查询有多少未分配的 rank 页，如果传递的 rank 非法，返回 `-EINVAL`

你需要确保你的分配算法可以通过测试并输出。最终测试通过比对输出进行评分。  