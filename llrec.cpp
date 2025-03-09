#include "llrec.h"


//*********************************************
// Provide your implementation of llpivot below
//*********************************************


void llpivot(Node *&head, Node *&smaller, Node *&larger, int pivot){
 if(head == nullptr){
   smaller = nullptr;
   larger = nullptr;
   return;
 }


 Node* next = head->next;
 head->next = nullptr;


 llpivot(next, smaller, larger, pivot);


 if(head->val <= pivot){
   head->next = smaller;
   smaller = head;
 }
 else{
   head->next = larger;
   larger = head;
 }
 head = nullptr;
}
