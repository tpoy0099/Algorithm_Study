#ifndef Algo_StringKMP_H
#define Algo_StringKMP_H
/*
KMP
基本思路是找出串内重复出现的模式,充分利用已匹配过的信息
从而在中断匹配时(遇到不等元素)不必每次都回到串头,节约循环次数

预处理:
寻找串T中当游标处于i+1位置时
最大的k,使得T[0]~T[k] == T[i-k]~T[i] (0 <= k < i)
{T[0]...T[k]},T[k+1]......{T[i-k]...T[i]}, T[i+1] 花括号内完全匹配
从而当比较至T[i+1]不等时, 如果T[k+1] != T[i+1]
子串T可以快速回溯到T[k+1] 减少重复的比较

定义T串用于存储一一对应的回溯位置的数组Next
给予Next[0],即T的首元素特殊标记 -1 (因为到头了,无法继续回溯)
如果T[k]存在前后相等的真缀,Next[k] = 真前缀尾元素下标
如果不存在,Next[k] = 0 回到首元素进行朴素比较

Next生成这是一个循环迭代的过程
找到第一个相等的个体,然后一点一点往后攒
遇见不等的缩小子串范围往回找
直到相等或者回头串头

主匹配:
主串S与匹配串T
1.如果S[i] == T[j], 继续比较两者的下一位
2.如果S[i] != T[j], 比较S[i] 与 T[Next[j]]
  如果Next[j] == -1, 表示回溯到了串头且串头也不等, i+=1 重新开始比较
循环过程2 直到出现1 或者长度溢出

Next预处理二段优化:
如果存在T[0]~T[k] == T[i-k]~T[i]
且T[k+1] == T[i+1]
则Next[i+1] 直接回溯到 Next[k+1]

朴素算法(双循环)的时间复杂度为O(m*n)
KMP为O(m+n)

疑问:
O(m+n)如何证明?, NextK内循环其实是一个小于i随机数?


2014.09.26 by Tpoy
*/

void ScanNextK(const char *T, int vNext[]) {
    int p = -1, s = 0; //prefix, suffix

    vNext[0] = -1;

    while (T[s]) {
        if (p == -1 || T[p] == T[s]) {
            ++p, ++s;
            vNext[s] = T[p] == T[s] ? vNext[p] : p;
        }
        else
            p = vNext[p];
    }
}

/*
FindFirstSubStr()
找到Pattern位于Base内的第一个相等子串
并返回相等子串首元素的下标
如果异常或没有找到返回-1
startpos表示从Base的哪个下标开始往后查找
*/
int FindFirstSubStr(const char *Base, const char *Pattern, unsigned int StartPos = 0) {
    unsigned int i, j, LenB, LenP;
    int EquIndex = -1;

    i = 0, LenB = 0;
    while (Base[i]) {
        ++i, ++LenB;
    }
    j = 0, LenP = 0;
    while (Pattern[j]) {
        ++j, ++LenP;
    }

    if (LenB >= LenP && LenP > 0 && StartPos <= LenB - LenP) {
        int *vNext = new int[LenP + 1];
        ScanNextK(Pattern, vNext);

        i = StartPos, j = 0;
        while (Base[i]) {
            if (j == -1 || Base[i] == Pattern[j]) {
                ++i, ++j;
            }
            else {
                j = vNext[j];
                continue;
            }

            if (j == LenP) {
                EquIndex = i - LenP;
                break;
            }
        }

        delete[] vNext;
    }

    return EquIndex;
}

#endif