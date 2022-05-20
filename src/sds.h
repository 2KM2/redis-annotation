#pragma once

/**
 * @brief 最大预分配长度
 * 
 */
#define SDS_MAX_PREALLOC (1024*1024)

#include <sys/types.h>
#include <stdarg.h>

/**
 * @brief 类型别名，用于指向 sdshdr 的 buf 属性
 * 
 */
typedef char * sds;

/*
 * 保存字符串对象的结构
 * sizeof(struct sdshdr) 8
 */
struct sdshdr
{
    // buf 中已占用空间的长度
    int len;

    // buf 中剩余可用空间的长度
    int free;

    // 数据空间
    char buf[]; //字节数组
};


/*
 * 返回 sds 实际保存的字符串的长度
 *
 * T = O(1)
 */
static inline size_t sdslen(const sds s) {
    struct sdshdr *sh = (struct sdshdr*)(s-(sizeof(struct sdshdr)));
    return sh->len;
}


/*
 * 返回 sds 可用空间的长度
 *
 * T = O(1)
 */
static inline size_t sdsavail(const sds s) {
    struct sdshdr *sh = (struct sdshdr*)(s-(sizeof(struct sdshdr)));
    return sh->free;
}



sds sdsnewlen(const void *init, size_t initlen);
sds sdsnew(const char *init);
sds sdsempty(void);
size_t sdslen(const sds s);
sds sdsdup(const sds s);
void sdsfree(sds s);
size_t sdsavail(const sds s);
sds sdsgrowzero(sds s, size_t len);
sds sdscatlen(sds s, const void *t, size_t len);
sds sdscat(sds s, const char *t);
sds sdscatsds(sds s, const sds t);
sds sdscpylen(sds s, const char *t, size_t len);
sds sdscpy(sds s, const char *t);