#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include"biginteger.h"
struct node{
    int data;
    struct node *next;
};
struct node *newnode(int data) {
    struct node *newnode = (struct node *)malloc(sizeof(struct node));
    if ( newnode == NULL) {
        printf("memory allocation failed!\n");
        return NULL;
    }
    newnode->data = data;
    newnode->next = NULL;
    return newnode;
}
struct node *insert_node(struct node *head, int num) {
    struct node *newnode = (struct node *)malloc(sizeof(struct node));
    if (newnode == NULL) {
        printf("Memory allocation failed!\n");
        return head;
    }
    newnode->data = num;
    newnode->next = NULL;
    if (head == NULL) {
        head = newnode;
    } else {
        struct node *current = head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newnode;
    }
    return head;
}
void display(struct node *head) {
    struct node *temp = head;
    while (temp != NULL) {
        printf(" %d\t", temp->data);
        temp = temp->next;
    }
printf("\n");
}
struct node *arraytolist(char arr[]) {
    int i = 0, num;
    struct node *head = NULL;
    while (i < strlen(arr)-1) {
        if (isdigit(arr[i])){
        num = (int)arr[i] - '0';
        head = insert_node(head, num);}
        i++;
    }
    return head;
}
struct node *reverse(struct node*head)
{
    if(head==NULL)
    {
        return head;
    }
    struct node* c=NULL;
    struct node* f=head->next;
    head->next=NULL;
    while(f!=NULL)
    {
        c=f;
        f=f->next;
        c->next=head;
        head=c;
    }
    return head;
}
struct node *push(struct node*head,int data)
{
    struct node *newnode=(struct node*)malloc(sizeof(struct node));
    newnode->data=data;
    newnode->next=head;
    head=newnode;
    return head;
}
void backnum(struct node*head)
{
    struct node*temp=head;
    printf("the sum is:\n");
    while(temp!=NULL)
    {
        printf("%d",temp->data);
        temp=temp->next;
    }
}
struct node* add(struct node* h1, struct node* h2) {
    struct node* result = NULL;
    int c = 0;
    while (h1 != NULL || h2 != NULL || c != 0) {
        int s=0,c=0;
        if (h1 != NULL) {
            s =s+ h1->data;
            h1 = h1->next;
        }
        if (h2 != NULL) {
            s =s+ h2->data;
            h2 = h2->next;
        }
        c = s / 10;
        s =s% 10;
        result = insert_node(result, s);
    }
    return result;
}
struct node* subtract(struct node* h1, struct node* h2) {
    struct node* temp1 = h1;
    struct node* temp2 = h2;
    struct node* result = NULL;
    struct node* ptr = NULL;
    int borrow = 0;
    if (h2 == NULL)
        return h1;
    if (h1 == NULL) {
        h2->data = -(h2->data);
        return h2;
    }
    while (temp1 != NULL || temp2 != NULL) {
        int num1 = (temp1 != NULL) ? temp1->data : 0;
        int num2 = (temp2 != NULL) ? temp2->data : 0;
        int diff = borrow + num1 - num2;
        if (diff < 0) {
            diff =diff+ 10;
            borrow = -1;
        } else {
            borrow = 0;
        }
        struct node* new_node = newnode(diff);
        if (result == NULL) {
            result = new_node;
            ptr = result;
        } else {
            ptr->next = new_node;
            ptr = ptr->next;
        }
        if (temp1 != NULL)
            temp1 = temp1->next;
        if (temp2 != NULL)
            temp2 = temp2->next;
    }
    return reverse(result);
}
void addtwoll(struct node* h1, struct node* r) {
    struct node* c1 = h1;
    struct node* c2 = r;
    int carry = 0;
    while (c1 != NULL || carry != 0) {
        int sum = carry + (c1 != NULL ? c1->data : 0) + (c2->next != NULL ? c2->next->data : 0);
        int digit = sum % 10;
        carry = sum / 10;
        if (c2->next != NULL) {
            c2->next->data = digit;
        } else {
            c2->next = newnode(digit);
        }
        if (c1 != NULL) {
            c1 = c1->next;
        }
        c2 = c2->next;
    }
}
struct node* mult_LL_with_digit(struct node* head, int digit) {
    struct node* temp = newnode(0);
    struct node* ac = temp;
    struct node* curr = head;
    int carry = 0;
    while (curr != NULL || carry != 0) {
        int sum = carry + (curr != NULL ? curr->data : 0) * digit;
        carry = sum / 10;
        int digit_sum = sum % 10;
        ac->next = newnode(digit_sum); 
        ac = ac->next;  
        if (curr != NULL) {
            curr = curr->next;
        }
    }
    return temp->next;  
}
struct node* multiplytwoLL(struct node* h1, struct node* h2) {
    struct node* L2_itr = h2;
    struct node* temp = newnode(0);  
    struct node* resitr = temp;
    while (L2_itr != NULL) {
        struct node* prd = mult_LL_with_digit(h1, L2_itr->data);
        L2_itr = L2_itr->next;
        addtwoll(prd, resitr);
        resitr = resitr->next;
    }
    struct node* result = temp->next;  
    free(temp);  
    return result;  
}
