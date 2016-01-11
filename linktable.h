#ifndef LINKTABLE_H
#define LINKTABLE_H

#include <iostream>
#include <stdlib.h>

using namespace std;

typedef struct _LinkNode
{
    int x_pos;
    int y_pos;
    struct _LinkNode * next;
}LinkNode;

class LinkTable
{
public:
    LinkTable();
    bool reInitialLink();                  //初始化链表,只需要在链表有数据的时候调用，用于删除节点数据
    bool insertPoint(int x,int y);       //插入节点
    bool deletePoint(LinkNode* node);     //删除节点
    int getLinkLength();                 //获取链表的长度
    LinkNode* getHead();                  //获取头结点
    ~LinkTable();
private:
    LinkNode* HeadNode;
    LinkNode* rearNode;
    int length;
};

#endif // LINKTABLE_H
