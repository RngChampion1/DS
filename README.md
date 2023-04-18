# DS
1.Vector文件里有Vector.h文件和Vector_fun.h文件，前者是向量模板类（数据结构与算法p30），后是具体实现前者功能的代码。
2. complex文件里有complex.h和main.cpp文件，前者定义了一个复数类，里面包含了实部、虚部，模等内容。main文件通过调用complex.h、Vector.h、Vector_fun.h文件， 实现了各种功能。 (1)通过rand()函数，先生成无序的复数向量，然后调用向量模板类中的unsort、find、insert、remove、deduplicate函数分别实现无序向量的置乱、查找、删除、唯一化操作。 (2)通过调用bubbleSort和mergeSort函数，对两组乱序向量排序，然后用clock函数计时，分别得到乱序情况下两种排序方法所化的时间。此后两组向量已经有序，再调用clock函数，得到顺序下两种算法的时间，再调用一个倒序函数（书里没有，自己定义的，其实就是稍微修改了一下书本中的bubble函数和bubbleSort函数),调用clock函数，得到倒序下两种算法的时间。有结果可知，归并排序算法更有效率。 (3)查找模介于两数之间的所有元素，我定义了一个int Find(int min, int max, Rank lo, Rank hi)函数，它能够返回符合要求的元素个数。
