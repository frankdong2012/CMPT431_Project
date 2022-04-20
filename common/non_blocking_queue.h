#include "allocator.h"
#include "utils.h"
#define LFENCE asm volatile("lfence" : : : "memory")
#define SFENCE asm volatile("sfence" : : : "memory")
const uint64_t mask = (uint64_t) 0x00FFFFFFFFFFFF;
template<class P>
struct pointer_t {
    P* ptr; 
    P* address(){
        return (P*) ((uint64_t) ptr & (uint64_t) 0x00FFFFFFFFFFFF);
    }
    uint count(){
        return (uint) (uint64_t)ptr & (uint64_t) 0xFFFF000000000000;
    }
    P* newPointr(P* address, uint count) {
        return (P*) ((uint64_t) address | ((uint64_t) count & 0xFFFF000000000000));
    }
};

// CAS operation
template <class ET>
inline bool CAS(ET *ptr, ET oldv, ET newv)
{
  if (sizeof(ET) == 1)
  {
    return __sync_bool_compare_and_swap((bool *)ptr, *((bool *)&oldv), *((bool *)&newv));
  }
  else if (sizeof(ET) == 4)
  {
    return __sync_bool_compare_and_swap((int *)ptr, *((int *)&oldv), *((int *)&newv));
  }
  else if (sizeof(ET) == 8)
  {
    return __sync_bool_compare_and_swap((long *)ptr, *((long *)&oldv), *((long *)&newv));
  }
  else
  {
    std::cout << "CAS bad length : " << sizeof(ET) << std::endl;
    abort();
  }
}


template <class T>
class Node
{
public:
    T value; 
    pointer_t <Node<T>> next; 
};

template <class T>
class NonBlockingQueue
{
public:
    pointer_t <Node<T>> q_head; 
    pointer_t <Node<T>> q_tail; 
    CustomAllocator my_allocator_;
    
    NonBlockingQueue() : my_allocator_()
    {
        //std::cout << "Using NonBlockingQueue\n";
    }

    void initQueue(long t_my_allocator_size){
        //std::cout << "Using Allocator\n";
        my_allocator_.initialize(t_my_allocator_size, sizeof(Node<T>));
        // Initialize the queue head or tail here
        Node<T>* newNode = (Node<T>*)my_allocator_.newNode();
        newNode->next.ptr = nullptr; 
        q_head.ptr = newNode; 
        q_tail.ptr = newNode; 
        my_allocator_.freeNode(newNode);
    }

    void enqueue(T value)
    {
        Node<T>* node = (Node<T>*)my_allocator_.newNode();
        node->value=value; 
        node->next.ptr = NULL; 
        pointer_t <Node<T>> tail; 
        pointer_t <Node<T>> node_ptr; 
        SFENCE; 
        while(true){
            tail = q_tail; 
            LFENCE; 
            pointer_t<Node<T>> next = tail.address()->next; 
            LFENCE;
            if(tail.ptr == q_tail.ptr){
                if(next.address() == NULL){
                    node_ptr.ptr = node_ptr.newPointr(node, next.count()+1);
                    if(CAS(&tail.address()->next, next, node_ptr)){
                        break;
                      }
                }
                    else{
                        node_ptr.ptr = node_ptr.newPointr(next.address(), tail.count()+1);
                        CAS(&q_tail, tail, node_ptr);
                 } 
                
            }
        }
        SFENCE;
	node_ptr.ptr = node_ptr.newPointr(node, tail.count()+1);
        CAS(&q_tail, tail, node_ptr);
        SFENCE;
        // Use LFENCE and SFENCE as mentioned in pseudocode
    }

    bool dequeue(T *value)
    {
        pointer_t<Node<T>> head;
        pointer_t<Node<T>> tail;
        pointer_t<Node<T>> next;
        pointer_t<Node<T>> node_ptr;
        while(true){
            head = q_head;
            LFENCE;
            tail = q_tail; 
            LFENCE;
            next = head.address()->next;
            LFENCE;
            if(head.address() == q_head.address()){
                if(head.address() == tail.address()){
                    if(next.address() == NULL){
                        return false; 
                    }    
                    node_ptr.ptr = node_ptr.newPointr(next.address(), tail.count()+1);    
                    CAS(&q_tail, tail, node_ptr);
                }
                else{
                    *value = next.address()->value;
                    node_ptr.ptr = node_ptr.newPointr(next.address(), head.count()+1);
                    if(CAS(&q_head, head, node_ptr)){
                        break;
                    }    
                }
            }
        }
        
        my_allocator_.freeNode(head.address());
        return true; 
    }

    void cleanup()
    {
        my_allocator_.cleanup();
    }

};

