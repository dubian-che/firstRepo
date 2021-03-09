# 算法数据结构

## 392.漂亮数组
*分治*
```
1.输入一个int类型的值N，构造一个长度为N的数组arr并返回；
要求：
对任意i<k<j,都满足arr[i]+arr[j]!=arr[k]*2
```

```c++
void func(vector<int>&T ,vector<int>&T1)
{
    int i = 0;
    while(T[i]!= 0)
    {
        T1[i] = T[i] * 2;
        i++;
    }
    int j = i;
    i = 0;
    while(T[i]!= 0)
    {
        T1[j] = T[i] * 2 - 1;
        j++;
        i++;
    }
    T = T1;
}

class Solution {
public:
    vector<int> beautifulArray(int N) {
        if(1 == N)
        {
            vector<int> T(1, 1);
            return T;
        }
        
        vector<int> T;
        int Q = pow(2, ceil((float)(log(N)/log(2))));
        printf("q:%d", Q);
        T.resize(Q);
        T.assign(Q, 0);
        T[0] = 2;
        T[1] = 1;
        vector<int> T1 = T;
        while(T[N - 1] == 0)
        {
            func(T, T1);
        }
        int k = 0;
        for(int j = 0; j < N; j++)
        {
            while(T1[k] > N)
            {
                k++;
            }
            T[j] = T1[k];
            k++;
        }
        T.resize(N);
        return T;
    }
};
```

## 2
```
长度为N
```