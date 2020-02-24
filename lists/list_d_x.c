
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h> 


/* List Node */

struct NODE
{
  int          data;          /* data */
  struct NODE  *prev_next;    /* prev and next pointer */
} ;

typedef struct NODE* NODE_PTR;

NODE_PTR head = NULL;
struct NODE *xor (struct NODE *p_prev, struct NODE *p_next);
struct NODE *insert(struct NODE **pp_head, int data);
void list_print(NODE_PTR head);

int main (int argc, char **args) 
{
  insert(&head, 6);
  insert(&head, 7);
  insert(&head, 8);
  insert(&head, 9);

  list_print(head);
}




/* xor - Finds XORed values of given NODE pointers
 *
 * Input :
 *      p_sentences   - List of sentences to be compared.
 *      max_sentences - Size of <p_sentences> can hold
 *      p_weights     - Pointer for returning weights should able to hold
 *                      <max_sentences> number of weights.
 * Output :
 *      p_weights - Weights
 *
 * Returns :
 *      Index for the sentence which matches closly.
 *
 * Description :
 *      Compares the object's sentence with given sentences, and returns the similarity
 * all given sentences in the form of weights. Also return the index of the sentence which matchs
 * closly with the given sentence.
 */

NODE_PTR xor (NODE_PTR prev, NODE_PTR next)
{
  return (struct NODE *)((uintptr_t)prev ^ (uintptr_t)next);
}

struct NODE *insert(NODE_PTR *head, int data)
{
  NODE_PTR new_node, next;

  /* get the new node */
  new_node = (struct NODE *)malloc(sizeof(struct NODE));

  /* set it's prev_next previous is NULL and Next is head */
  new_node->data = data;
  new_node->prev_next = xor(NULL, *head);

  /* set current head's prev_next */
  if (*head != NULL)
  {
    /* get the Next node to the head */
    next = xor(NULL, (*head)->prev_next);

    /* fix the prev_next node for the head */
    (*head)->prev_next = xor(new_node, next);
  }

  /* change the head */
  *head = new_node;

  return new_node;
}



void list_print(NODE_PTR head)
{
 NODE_PTR current, next, previous;
 
  current  = head;
  previous = NULL;
  next     = NULL;

  while (current != NULL)
  {
    printf ("Data %d\n", current->data);
    next = xor(previous, current->prev_next);
    previous = current;
    current  = next;
  }

}



