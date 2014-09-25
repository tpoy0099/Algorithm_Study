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


朴素算法(双循环)的时间复杂度为O(m*n)
KMP为O(m+n)

疑问:
O(m+n)如何证明?, NextK内循环其实是一个小于i随机数?
其实KMP只在串的真前缀和真后缀存在大量一致的 子前缀==子后缀 时才高效?
*/

#ifndef Algo_StringKMP_H
#define Algo_StringKMP_H

void ScanNextK(const char *T, int vNext[]) {
    int p = -1, s = 0; //prefix, suffix

    vNext[0] = -1;

    while (T[s]) {
        if (p == -1 || T[p] == T[s]) {
            ++p, ++s;
            vNext[s] = p;
        }
        else
            p = vNext[p];
    }
}

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

        i = 0, j = 0;
        while (i < LenB) {
            if (j == -1 || Base[i] == Pattern[j]) {
                ++i, ++j;
            }
            else {
                j = vNext[j];
                continue;
            }

            if (j == LenP) 
                EquIndex = i - LenP;
        }

        delete[] vNext;
    }

    return EquIndex;
}



/*classical sample
void get_nextval(const char *T, int next[]) {
    int j = 0, k = -1;
    next[0] = -1;
    while (T[j] != '/0') {
        if (k == -1 || T[j] == T[k]) {
            ++j; ++k;
            if (T[j] != T[k])
                next[j] = k;
            else
                next[j] = next[k];
        }// if
        else
            k = next[k];
    }
}

int KMP(const char *Text, const char* Pattern)
{
    if (!Text || !Pattern || Pattern[0] == '/0' || Text[0] == '/0')
        return -1;
    
    int len = 0;
    const char * c = Pattern;
    while (*c++ != '/0')
        ++len;//字符串长度。
    
    int *next = new int[len + 1];
    get_nextval(Pattern, next);//求Pattern的next函数值

    int index = 0, i = 0, j = 0;
    while (Text[i] != '/0' && Pattern[j] != '/0') {
        if (Text[i] == Pattern[j]) {
            ++i;// 继续比较后继字符
            ++j;
        }
        else {
            index += j - next[j];
            if (next[j] != -1)
                j = next[j];// 模式串向右移动
            else {
                j = 0;
                ++i;
            }
        }
    }

    delete[] next;
    if (Pattern[j] == '/0')
        return index;// 匹配成功
    else
        return -1;
}*/

#endif