#include "sds.h"
#include <malloc.h>

/**
 * @brief 
 * 根据给定的初始化字符串 init 和字符串长度 initlen
 * 创建一个新的 sds
 * @param init    : 初始化字符串指针
 * @param initlen : 初始化字符串的长度
 * @return sds :    创建成功返回 sdshdr 相对应的 sds  创建失败返回 NULL
 */
sds sdsnewlen(const void *init, size_t initlen)
{
      struct sdshdr *sh;

      // 根据是否有初始化内容，选择适当的内存分配方式
      if(init)
      {
        // malloc 不初始化所分配的内存
          sh=(struct sdshdr *)malloc(sizeof(struct sdshdr)+initlen+1);
      }
      else
      {
          // calloc 将分配的内存全部初始化为 0
          sh=(struct sdshdr *)calloc(1,sizeof(struct sdshdr)+initlen+1);
      }

    // 内存分配失败，返回
    if (sh == NULL) return NULL;





    
}