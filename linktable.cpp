#include "linktable.h"

LinkTable::LinkTable()
{
    HeadNode = (LinkNode*)new LinkNode;
    HeadNode->x_pos = -1;
    HeadNode->y_pos = -1;
    HeadNode->next = NULL;       //头结点初始化
    rearNode = HeadNode;         //头结点
    length = 0;                  //链表长度
}

bool LinkTable::reInitialLink()
{
    if(HeadNode == NULL)
    {
        HeadNode = (LinkNode*) new LinkNode;
        HeadNode->x_pos = -1;
        HeadNode->y_pos = -1;
        HeadNode->next = NULL;
        rearNode = HeadNode;
        length = 0;
    }
    if(HeadNode->next == NULL)       //如果链表本来就为空，初始化成功
    {
        return true;
    }
    else
    {
        LinkNode* tempH = HeadNode->next;   //获取链表的后续节点
        HeadNode->next = NULL;              //链表置空
        rearNode = HeadNode;                //尾节点指向头结点，初始状态
        while(tempH != NULL)
        {
            LinkNode* tempN = tempH->next;
            delete tempH;
            length--;
            tempH = tempN;
        }
        if(HeadNode->next == NULL)
        {
            length = 0;
            return true;
        }
        else
        {
            return false;
        }
    }
}

//获取头结点
LinkNode *LinkTable::getHead()
{
    return HeadNode;
}

//插入节点
bool LinkTable::insertPoint(int x, int y)
{
    //LinkNode tempNode = (LinkNode)malloc(sizeof(*LinkNode));  //申请节点空间
    LinkNode* tempNode = new LinkNode;
    if(tempNode==NULL)
    {
        return false;
    }
    else
    {
        tempNode->x_pos = x;
        tempNode->y_pos = y;
        tempNode->next = NULL;

        rearNode->next = tempNode;
        rearNode = rearNode->next;
        length++;            //长度加1
        return true;
    }
}

//删除节点
bool LinkTable::deletePoint(LinkNode* node)
{
    LinkNode* tempNode = HeadNode->next;
    if(tempNode->next != NULL)
    {
        if(tempNode == node)
        {
            length--;        //长度减1
            return true;
        }
    }
    else
        return false;
}

//获取链表长度
int LinkTable::getLinkLength()
{
    return length;
}

LinkTable::~LinkTable()
{

}

