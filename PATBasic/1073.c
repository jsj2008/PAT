/**
 * 1073. 多选题常见计分法(20)
 * 
 * 批改多选题是比较麻烦的事情，有很多不同的计分方法。有一种最常见的计分方法是：如果考生
 * 选择了部分正确选项，并且没有选择任何错误选项，则得到50%分数；如果考生选择了任何一个
 * 错误的选项，则不能得分。本题就请你写个程序帮助老师批改多选题，并且指出哪道题的哪个选
 * 项错的人最多。
 * 
 * 
 * 输入格式：
 * 
 * 输入在第一行给出两个正整数N（<=1000）和M（<=100），分别是学生人数和多选题的个数。
 * 随后M行，每行顺次给出一道题的满分值（不超过5的正整数）、选项个数（不少于2且不超过5
 * 的正整数）、正确选项个数（不超过选项个数的正整数）、所有正确选项。注意每题的选项从
 * 小写英文字母a开始顺次排列。各项间以1个空格分隔。最后N行，每行给出一个学生的答题情
 * 况，其每题答案格式为“(选中的选项个数 选项1 ……)”，按题目顺序给出。注意：题目保证学
 * 生的答题情况是合法的，即不存在选中的选项数超过实际选项数的情况。
 * 
 * 输出格式：
 * 
 * 按照输入的顺序给出每个学生的得分，每个分数占一行，输出小数点后1位。最后输出错得最多
 * 的题目选项的信息，格式为：“错误次数 题目编号（题目按照输入的顺序从1开始编号）-
 * 选项号”。如果有并列，则每行一个选项，按题目编号递增顺序输出；再并列则按选项号递增顺
 * 序输出。行首尾不得有多余空格。如果所有题目都没有人错，则在最后一行输出“Too simple”。
 * 
 * 输入样例1：
 * 3 4 
 * 3 4 2 a c
 * 2 5 1 b
 * 5 3 2 b c
 * 1 5 4 a b d e
 * (2 a c) (3 b d e) (2 a c) (3 a b e)
 * (2 a c) (1 b) (2 a b) (4 a b d e)
 * (2 b d) (1 e) (1 c) (4 a b c d)
 * 
 * 输出样例1：
 * 3.5
 * 6.0
 * 2.5
 * 2 2-e
 * 2 3-a
 * 2 3-b
 * 
 * 输入样例2：
 * 2 2 
 * 3 4 2 a c
 * 2 5 1 b
 * (2 a c) (1 b)
 * (2 a c) (1 b)
 * 
 * 输出样例2：
 * 5.0
 * 5.0
 * Too simple
 */

#include <stdio.h>

#define MAX_M 100
#define MAX_OPTIONS 5

int readanswer()
{
    char c;
    int answer = 0, count;
    
    scanf("%d", &count);
    for(int i = 0; i < count; i++)
    {
        while((c = getchar()) == ' ');
        answer |= 1 << (c - 'a');
    }
    return answer;
}

int main()
{
    int N, M, full_score[MAX_M] = {0}, correct_ans[MAX_M] = {0}, 
        wrong_ans[MAX_M] = {0}, wrong_count[MAX_M][5] = {{0}},
        wrong_count_max = 0;
    
    scanf("%d %d", &N, &M);
    /* Read M lines */
    int count_options;
    for(int i = 0; i < M; i++)
    {
        scanf("%d %d", full_score + i, &count_options);
        correct_ans[i] = readanswer();
    }
    
    /* Read N lines */
    for(int i = 0; i < N; i++)
    {
        float score = 0;
        int answer;
        for(int j = 0; j < M; j++)
        {
            while(getchar() != '(');
            answer = readanswer();
            wrong_ans[j] = answer ^ correct_ans[j];
            
            if(wrong_ans[j] == 0)               /* all correct */
                score += full_score[j];
            else if((wrong_ans[j] | correct_ans[j]) == correct_ans[j])               
                score += 0.5 * full_score[j];   /* partially corrent */
            
            /* For every option, record the number of students got wrong */
            for(int k = 0; k < MAX_OPTIONS; k++)
            {
                wrong_count[j][k] += wrong_ans[j] >> k & 1; /* k-th bit */
                if(wrong_count[j][k] > wrong_count_max)
                    wrong_count_max = wrong_count[j][k];
            }
            
            while(getchar() != ')');
        }
        printf("%.1f\n", score);
    }
    
    if(wrong_count_max == 0)
        printf("Too simple");
    else
        for(int i = 0; i < M; i ++)
            for(int j = 0; j < MAX_OPTIONS; j++)
                if(wrong_count[i][j] == wrong_count_max)
                    printf("%d %d-%c\n", wrong_count_max, i + 1, j + 'a');

    return 0;
}
