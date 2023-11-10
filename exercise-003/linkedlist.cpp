#include "linkedlist.h"

LinkedList::~LinkedList()
{
  for (auto tmp = m_head; tmp != nullptr; tmp = tmp->pNext /* prepare the next in the row */) {
    auto elem = tmp; /* save the element to be deleted */
    delete elem;
  }
}

bool LinkedList::insert_tail(LinkedListNode *node)
{
  bool ret = false;
  if (nullptr == node) {
    return ret;
  }
  // insert your code here....
  if (m_head == nullptr) {
    m_head = node;
  } else {
    auto tmp = m_head;
    while (tmp->pNext != nullptr) {
      tmp = tmp->pNext;
    }
    tmp->pNext = node;
  }

  ret = true;
  return ret;

}

bool LinkedList::insert_head(LinkedListNode *node)
{
  bool ret = false;
  if (nullptr == node) {
    return ret;
  }
  // insert your code here....
  node->pNext = m_head;
  m_head = node;

  ret = true;
  return ret;
}

bool LinkedList::insert_after(LinkedListNode *loc, LinkedListNode *node)
{
  bool ret = false;
  if ((nullptr == loc) || (nullptr == node)) {
    return ret;
  }
  // insert your code here ....
  node->pNext = loc->pNext;
  loc->pNext = node;

  ret = true;
  return ret;
}

bool LinkedList::insert_before(LinkedListNode *loc, LinkedListNode *node)
{
  bool ret = false;
  if ((nullptr == loc) || (nullptr == node)) {
    return ret;
  }
  // Insert your code here....
  if (loc == m_head) {
    insert_head(node);
  } else {
    auto tmp = m_head;
    while (tmp->pNext != loc) {
      tmp = tmp->pNext;
    }
    tmp->pNext = node;
    node->pNext = loc;
  }

  ret = true;
  return ret;
}

bool LinkedList::remove(LinkedListNode *node)
{
  bool ret = false;
  // insert your code here ...
  if (node == nullptr) {
    return ret;
  }

  if (node == m_head) {
    m_head = node->pNext;
  } else {
    auto tmp = m_head;
    while (tmp->pNext != nullptr && tmp->pNext != node) {
      tmp = tmp->pNext;
    }

    if (tmp->pNext != nullptr) {
      tmp->pNext = node->pNext;
    }
  }

  delete node;
  ret = true;
  return ret;
}

size_t LinkedList::size()
{
  size_t count = 0;
  /* using a lambda to count objects in the list*/
  traverse([&count](LinkedListNode *node) { count++; });
  return count;
}


void LinkedList::traverse(std::function<void(const std::string &)> func)
{
  traverse([&](LinkedListNode *node) { func(node->m_name); });
}

void LinkedList::traverse(std::function<void(LinkedListNode *node)> func)
{
  for (auto tmp = m_head; tmp != nullptr; tmp = tmp->pNext) {
    func(tmp);
  }
}