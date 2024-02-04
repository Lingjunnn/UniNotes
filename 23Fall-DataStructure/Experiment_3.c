//һЩ�Ż�˼·��
//�����������ַ�������������֤һ�������ܲ�������������������ܾͿ���
#include <stdio.h>
#include <string.h>

typedef struct Node{ //���Ľڵ㶨��
    char symbol; //�洢���ַ�
    int frequency; //Ȩֵ
    struct Node *parent, *left, *right;
} Node;
Node HuffmanNode[200];

void NodeCreate(char data){ //���ַ���ת��Ϊ�ڵ㣬����Ȩֵ
    int flag = 0; //�����Ƿ�Ѱ�ҵ���ͬ�ַ�
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
int MinNodesMerge(){ //��û�и��ڵ�Ľڵ��У��ҵ�Ȩֵ��С�������ڵ�ϲ������½ڵ㣬��ֻ�и��ڵ㣬�򷵻ظ��ڵ��������е����
    int i = 0;
    //ָ���ʼ��
    while(HuffmanNode[i].parent != NULL){i++;}
    Node* min1 = HuffmanNode + i;
    i++;
    while(HuffmanNode[i].parent != NULL){i++;}
    if(HuffmanNode[i].frequency == '\0'){
        return i;
    }
    Node* min2 = HuffmanNode + i;
    //�����Ƚ�
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
void ReverseString(char encoding[210]){ //�����ӡ�ַ�������ӡ���з�
    int length = strlen(encoding);
    for(length--;length >= 0;length--){
        printf("%c",encoding[length]);
    }
    printf("\n");
}
void PrintTree(Node* node){ //��ӡ��Ӧ�ڵ�ı����
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
    //¼������
    printf("Hint: Please enter a string with a length less than 50!\n");
    printf("Enter the string to be encoded:");
    scanf("%s",data);
    //ͳ��Ƶ�ʣ��������ڵ�
    for(;data[i] != '\0';i++){
        NodeCreate(data[i]);
    }
    //���ɹ�������
    int root = 0;
    while(root == 0){
        root = MinNodesMerge();
    }
    root--;
    //��������
    printf("The corresponding encoding table is:\n");
    i = 0;
    Node* PrintedNode;
    for(;HuffmanNode[i].symbol != '\0';i++){
        PrintedNode = HuffmanNode + i;
        PrintTree(PrintedNode);
    }
}