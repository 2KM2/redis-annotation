#pragma once

/* Object types */
// 对象类型
#define REDIS_STRING 0
#define REDIS_LIST 1
#define REDIS_SET 2
#define REDIS_ZSET 3
#define REDIS_HASH 4



// 对象编码
#define REDIS_ENCODING_RAW 0     /* 简单动态字符串 */
#define REDIS_ENCODING_INT 1     /* long类型的整数 */
#define REDIS_ENCODING_HT 2      /* 字典*/
#define REDIS_ENCODING_ZIPMAP 3  /* Encoded as zipmap */
#define REDIS_ENCODING_LINKEDLIST 4 /* 双端列表 */
#define REDIS_ENCODING_ZIPLIST 5 /* 压缩列表 */
#define REDIS_ENCODING_INTSET 6  /* 整数集合 */
#define REDIS_ENCODING_SKIPLIST 7  /* 跳跃表*/
#define REDIS_ENCODING_EMBSTR 8  /* embstr编码的简单动态字符串 */




#define REDIS_LRU_BITS 24
#define REDIS_LRU_CLOCK_MAX ((1<<REDIS_LRU_BITS)-1) /* Max value of obj->lru */
#define REDIS_LRU_CLOCK_RESOLUTION 1000 /* LRU clock resolution in ms */
/**
 * @brief 创建键值对时候会形成两个对象 一个是键对象 一个是值对象
 *  每种类型的对象都是至少使用了两种不同的编码
 * REDIS_STRING:REDIS_ENCODING_RAW REDIS_ENCODING_INT REDIS_ENCODING_EMBSTR
 * 
 * REDIS_LIST:REDIS_ENCODING_ZIPLIST  REDIS_ENCODING_LINKEDLIST
 * 
 * REDIS_HASH:REDIS_ENCODING_ZIPLIST REDIS_ENCODING_HT
 * 
 * REDIS_SET: REDIS_ENCODING_INTSET REDIS_ENCODING_HT
 * 
 * REDIS_ZSET: REDIS_ENCODING_ZIPLIST REDIS_ENCODING_SKIPLIST
 */
typedef struct redisObject
{
    // 类型: 键都是字符串对象 
    unsigned type:4;

    // 编码
    unsigned encoding:4;

    // 对象最后一次被访问的时间
    unsigned lru:REDIS_LRU_BITS; /* lru time (relative to server.lruclock) */

    // 引用计数
    int refcount;

    // 指向实际值的指针
    void *ptr;
} robj;


