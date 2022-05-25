#include "sds.h"
#include <malloc.h>
<<<<<<< HEAD

=======
#include <string.h>
>>>>>>> 	modified:   README.md
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
<<<<<<< HEAD
        // malloc 不初始化所分配的内存
=======
        // malloc 不初始化所分配的内存 分配的是sdshdr 结构体
>>>>>>> 	modified:   README.md
          sh=(struct sdshdr *)malloc(sizeof(struct sdshdr)+initlen+1);
      }
      else
      {
          // calloc 将分配的内存全部初始化为 0
          sh=(struct sdshdr *)calloc(1,sizeof(struct sdshdr)+initlen+1);
      }

    // 内存分配失败，返回
    if (sh == NULL) return NULL;

<<<<<<< HEAD




    
=======
    sh->len=initlen;
    sh->free=0;

    // 如果有指定初始化内容，将它们复制到 sdshdr 的 buf 中
    if(initlen &&init)
    memcpy(sh->buf, init, initlen);

    sh->buf[initlen]='\0';


  // 返回 buf 部分，而不是整个 sdshdr
    return (char*)sh->buf;
}

/**
 * @brief 根据给定字符串 init ，创建一个包含同样字符串的 sds
 * 
 * @param init 
 *  init: 如果输入为NULL 那么创建一个空白的sds
 *   否则,新建的sds中包含和init内容相同的字符串
 * @return sds 
 * sds: 创建成功返回sdshdr相对应的sds
 * 创建失败返回NULL
 */
sds sdsnew(const char *init)
{
    size_t initlen=(init==NULL)?0:strlen(init);
    return sdsnewlen(init,initlen);
}
/**
 * @brief 复制给定的sds副本
 * 
 * @param s 
 * @return sds 
 * sds ：创建成功返回输入 sds 的副本
 *        创建失败返回 NULL
 */
sds sdsdup(const sds s){
    return sdsnewlen(s,sdslen(s));
}

/**
 * @brief 释放给定的 sds
 * 
 * @param s 
 */
void sdsfree(sds s)
{
    if(s==NULL) return;
   free(s-sizeof(struct sdshdr));
}

/**
 * @brief  将 sds 扩充至指定长度，未使用的空间以 0 字节填充。
 * 
 * @param s 
 * @param len 
 * @return sds 
 * sds: 扩充成功返回新sds, 失败返回NULL
 */
sds sdsgrowzero(sds s, size_t len)
{
    struct sdshdr *sh = (struct sdshdr*)(s-(sizeof(struct sdshdr)));
    size_t totlen,curlen =sh->len;

    //如果len比字符串的xian


}
/**
 * @brief  将长度为 len 的字符串 t 追加到 sds 的字符串末尾
 * 
 * @param s 
 * @param t 
 * @param len 
 * @return sds 
 * sds ：追加成功返回新 sds ，失败返回 NULL
 * 
 */
sds sdscatlen(sds s, const void *t, size_t len)
{
    struct sdshdr *sh;
    
    // 原有字符串长度
    size_t curlen = sdslen(s);

    // 扩展 sds 空间
    // T = O(N)
    /**
     * TODO: 如果发生了扩容 调用的是realloc 在原来基础上会进行扩容 不需用 memcpy
     * 
     */
    s = sdsMakeRoomFor(s,len);

    // 内存不足？直接返回
    if(s==NULL) return NULL;


    
    // 复制 t 中的内容到字符串后部
    // T = O(N)
    sh = (struct sdshdr *) (s-(sizeof(struct sdshdr)));
    memcpy(s+curlen, t, len);


    // 更新属性
    sh->len = curlen+len;
    sh->free = sh->free-len;

    // 添加新结尾符号
    s[curlen+len] = '\0';

    // 返回新 sds
    return s;

}


/**
 * @brief 将给定字符串 t 追加到 sds 的末尾
 * 
 * @param s 
 * @param t 
 * @return sds 
 * sds ：追加成功返回新 sds ，失败返回 NULL
 */
sds sdscat(sds s, const char *t)
{ 
  return sdscatlen(s,t,strlen(t));
}



/**
 * @brief  * 对 sds 中 buf 的长度进行扩展，确保在函数执行之后，
 *  buf 至少会有 addlen + 1 长度的空余空间
 * （额外的 1 字节是为 \0 准备的）
 * 
 * @param s 
 * @param addlen 
 * @return sds 
 * sds ：扩展成功返回扩展后的 sds
 *        扩展失败返回 NULL
 */
sds sdsMakeRoomFor(sds s, size_t addlen)
{
     struct sdshdr *sh, *newsh;
      // 获取 s 目前的空余空间长度
    size_t free = sdsavail(s);
    size_t len,newlen;

     // s 目前的空余空间已经足够，无须再进行扩展，直接返回
     if(free>=addlen) return s;

    // 获取 s 目前已占用空间的长度
    len=sdslen(s);

    sh = ( struct sdshdr *) (s-(sizeof(struct sdshdr)));

    // s 最少需要的长度
    newlen = (len+addlen);

  // 根据新长度，为 s 分配新空间所需的大小
    if(newlen<SDS_MAX_PREALLOC){
          // 如果新长度小于 SDS_MAX_PREALLOC 
        // 那么为它分配两倍于所需长度的空间
        newlen *= 2;
    }
    else 
         // 否则，分配长度为目前长度加上 SDS_MAX_PREALLOC
        newlen += SDS_MAX_PREALLOC;
    /**
     * @brief user
     * 
     */
    newsh = (struct sdshdr*)realloc(sh, sizeof(struct sdshdr)+newlen+1);
  
    // 内存不足，分配失败，返回
    if (newsh == NULL) return NULL;

    // 更新 sds 的空余长度
    newsh->free = newlen - len;

    // 返回 sds
    return newsh->buf;
}
void sdsIncrLen(sds s, int incr)
{

}
/**
 * @brief 回收 sds 中的空闲空间，回收不会对 sds 中保存的字符串内容做任何修改。
 * 
 * @param s 
 * @return sds 
 */
sds sdsRemoveFreeSpace(sds s)
{
  struct sdshdr *sh=(struct sdshdr*)(s-(sizeof(struct sdshdr)));

  // 进行内存重分配，让 buf 的长度仅仅足够保存字符串内容
  sh=(struct sdshdr*)realloc(sh, sizeof(struct sdshdr)+sh->len+1);

  // 空余空间为 0
    sh->free = 0;

    return sh->buf;
}
/**
 * @brief 返回给定 sds 分配的内存字节数
 * 
 * @param s 
 * @return size_t 
 */
size_t sdsAllocSize(sds s)
{
  struct sdshdr *sh=(struct sdshdr*)(s-(sizeof(struct sdshdr)));

  return sizeof(*sh)+sh->len+sh->free+1;
}

/**
 * @brief  在不释放 SDS 的字符串空间的情况下，
 *        重置 SDS 所保存的字符串为空字符串
 * 
 * @param s 
 */
void sdsclear(sds s)
{
  // 取出 sdshdr
    struct sdshdr *sh = (struct sdshdr*) (s-(sizeof(struct sdshdr)));
 // 重新计算属性
    sh->free += sh->len;
    sh->len = 0;

    // 将结束符放到最前面（相当于惰性地删除 buf 中的内容）
    sh->buf[0] = '\0';


>>>>>>> 	modified:   README.md
}