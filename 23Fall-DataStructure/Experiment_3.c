//一些优化思路：
//·输入中文字符报错，或者先验证一下中文能不能正常输入输出，不能就砍掉
#include <stdio.h>
#include <string.h>

typedef struct Node{ //树的节点定义
    char symbol; //存储的字符
    int frequency; //权值
    struct Node *parent, *left, *right;
} Node;
Node HuffmanNode[200];

void NodeCreate(char data){ //将字符串转化为节点，并赋权值
    int flag = 0; //表明是否寻找到相同字符
    int i = 0;
    for(;HuffmanNode[i].symbol != '\0' && flag == 0;i++){
        if(data == HuffmanNode[i].symbol){
            HuffmanNode[i].frequency++;
            flag = 1;
        }
    }
    if(flag == 0){
        HuffmanNode[i].symbol = data;
        HuffmanNode[i].frequency = 1;
    }
}
int MinNodesMerge(){ //在没有父节点的节点中，找到权值最小的两个节点合并生成新节点，若只有根节点，则返回根节点在数组中的序号
    int i = 0;
    //指针初始化
    while(HuffmanNode[i].parent != NULL){i++;}
    Node* min1 = HuffmanNode + i;
    i++;
    while(HuffmanNode[i].parent != NULL){i++;}
    if(HuffmanNode[i].frequency == '\0'){
        return i;
    }
    Node* min2 = HuffmanNode + i;
    //遍历比较
    i = 0;
    int frequency;
    for(;HuffmanNode[i].frequency != '\0';i++){
        frequency = HuffmanNode[i].frequency;
        if(HuffmanNode[i].parent == NULL && min1 != HuffmanNode + i && min2 != HuffmanNode + i){
            if(min1->frequency > min2->frequency){
                if(min1->frequency > frequency){
                    min1 = HuffmanNode + i;
                }
            }
            if(min1->frequency < min2->frequency){
                if(min2->frequency > frequency){
                    min2 = HuffmanNode + i;
                }
            }
        }
    }
    HuffmanNode[i].frequency = min1->frequency + min2->frequency;
    HuffmanNode[i].left = min1;
    HuffmanNode[i].right = min2;
    min1->parent = HuffmanNode + i;
    min2->parent = HuffmanNode + i;
    return 0;
}
void ReverseString(char encoding[210]){ //倒序打印字符串并打印换行符
    int length = strlen(encoding);
    for(length--;length >= 0;length--){
        printf("%c",encoding[length]);
    }
    printf("\n");
}
void PrintTree(Node* node){ //打印相应节点的编码表
    char encoding[210] = "";
    Node* temp;
    int i = 0;
    printf("%c ",node->symbol);
    while(node->parent != NULL){
        temp = node;
        node = node->parent;
        if(node->left == temp){
            encoding[i] = '0';
        } else {
            encoding[i] = '1';
        }
        i++;
    }
    ReverseString(encoding);
}

int main(){
    char data[55];
    int i = 0;
    //录入数据
    printf("Hint: Please enter a string with a length less than 50!\n");
    printf("Enter the string to be encoded:");
    scanf("%s",data);
    //统计频率，并创建节点
    for(;data[i] != '\0';i++){
        NodeCreate(data[i]);
    }
    //生成哈夫曼树
    int root = 0;
    while(root == 0){
        root = MinNodesMerge();
    }
    root--;
    //输出编码表
    printf("The corresponding encoding table is:\n");
    i = 0;
    Node* PrintedNode;
    for(;HuffmanNode[i].symbol != '\0';i++){
        PrintedNode = HuffmanNode + i;
        PrintTree(PrintedNode);
    }
}