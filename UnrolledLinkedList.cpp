#include"UnrolledLinkedList.h"
void UnrolledLinkedList::add(int val) {
	size++;
	if (head == NULL) {
		head = new Node(nodeSize);
		head->add(val);
		tail = head;
		numOfNodes++;
		return;
	}
	if (tail->isFull() == false) {
		/*if (tail->prev != NULL) {
			if (tail->prev->isFull() == false) {
				tail->prev->add(tail->elements[0]);
				tail->removeAt(0);
				tail->add(val);
				return;
			}
		}*/
		tail->add(val);
		return;
	}
	else {
		numOfNodes++;
		Node* pNew = new Node(nodeSize);
		for (int i = tail->getHalfNodeSize(); i < tail->numElements; i++)
			pNew->add(tail->elements[i]);
		pNew->add(val);
		for (int i = tail->numElements - 1; i >= tail->getHalfNodeSize(); i--)
			tail->removeAt(i);
		tail->next = pNew;
		pNew->prev = tail;
		tail = pNew;
	}
}

int UnrolledLinkedList::getAt(int pos) {
	if (pos < 0 || pos >= size)
		throw "IndexOutOfBoundsException"; // check whether pos is valid or not
	int count = 0;
	for (Node*p = head; p != NULL; p = p->next)
	{
		for (int i = 0; i < p->numElements; i++)
		{
			if (count == pos) 
				return p->elements[i];
			count++;
		}
	}
}

void UnrolledLinkedList::setAt(int pos, int val) {
	if (pos < 0 || pos >= size)
		throw "IndexOutOfBoundsException"; // check whether pos is valid or not
	int count = 0;
	if (head == NULL)
		return;
	for (Node*p = head; p != NULL; p = p->next)
	{
		for (int i = 0; i < p->numElements; i++) {
			if (count == pos) {
				p->removeAt(i);
				p->insertAt(i, val);
				return;
			}
			count++;
		}
	}
}


void UnrolledLinkedList::insertAt(int pos, int val) {
	if (pos < 0 || pos > size)
		throw "IndexOutOfBoundsException"; // check whether pos is valid or not	

	if (head == NULL) {
		if (pos == 0) {
			size++;
			head = new Node(nodeSize);
			head->add(val);
			tail = head;
			numOfNodes++;
			return;
		}
	}
	else {
		if (pos == size)
			add(val);
		else {
			int count = 0;
			for (Node*p = head; p != NULL; p = p->next) {
				for (int i = 0; i < p->numElements; i++) {
					if (count == pos) {
						if (p->isFull() == false)
						{
							size++;
							p->insertAt(i, val);
							return;
						}
						else {
							size++;
							int x = p->elements[p->numElements - 1];
							p->removeAt(p->numElements - 1);
							p->insertAt(i, val);
							//t?o node m?i

							
							Node* pNew = new Node(nodeSize);
							numOfNodes++;
							for (int k = p->getHalfNodeSize(); k < p->numElements; k++) {
								pNew->add(p->elements[k]);
							}
							pNew->add(x);
							// xoa các ph?n t? dã chuy?n qua pNew
							for (int k = p->numElements - 1; k >= p->getHalfNodeSize(); k--) {
								p->removeAt(k);
							}
							// noi pNew
							pNew->next = p->next;
							p->next = pNew;
							pNew->prev = p;
							if (pNew->next != NULL)
								pNew->next->prev = pNew;
							if (p == tail)
								tail = pNew;
							return;
						}
					}
					count++;
				}
			}
		}
	}
}

void UnrolledLinkedList::deleteAt(int pos)
{
	if (pos < 0 || pos >= size)
		throw "IndexOutOfBoundsException"; // check whether pos is valid or not
	size--;
	if (numOfNodes == 1)
	{
		if (size == 0) {
			head->removeAt(0);
			Node*temp = head;
			delete temp;
			head = tail = NULL;
			numOfNodes--;
			return;
		}
		else {
			head->removeAt(pos);
			return;
		}
	}
	int count = 0;
	for (Node*p = head; p != NULL; p = p->next) {
		for (int i = 0; i < p->numElements; i++) {
			if (count == pos) {
				if (p->numElements > p->getHalfNodeSize()) {
					p->removeAt(i);
					return;
				}
				else {
					if (p == head) {
						if (p->next->numElements > p->next->getHalfNodeSize()) {
							p->removeAt(i);
							p->add(p->next->elements[0]);
							p->next->removeAt(0);
							return;
						}
						else {
							p->removeAt(i);
							for (int k = 0; k < p->next->getHalfNodeSize(); k++)
								p->add(p->next->elements[k]);
							// delete node p->next after Merger
							for (int k = p->next->getHalfNodeSize() - 1; k >= 0; k--)
								p->next->removeAt(k);
							Node* temp = p->next;
							// Change next only if node to be deleted is NOT the last node 
							if (temp->next != NULL) {
								temp->next->prev = temp->prev;
							}
							else {
								tail = temp->prev;
							}

							// Change prev only if node to be deleted is NOT the first node
							if (temp->prev != NULL) {
								temp->prev->next = temp->next;
							}
							delete temp;
							numOfNodes--;
							return;
						}
					}
					else if (p == tail) {
						if (p->prev->numElements > p->prev->getHalfNodeSize()) {
							p->removeAt(i);
							// l?y ph?n t? cu?i c?a p->prev luu vào x
							int x = p->prev->elements[p->prev->numElements - 1];
							p->insertAt(0, x);
							p->prev->removeAt(p->prev->numElements - 1);
							return;
						}
						else {
							p->removeAt(i);
							for (int k = 0; k < p->numElements; k++) {
								p->prev->add(p->elements[k]);
							}

							// delete node p after Merger
							for (int k = p->numElements - 1; k >= 0; k--) {
								p->removeAt(k);
							}

							Node* temp = p;
							// Change next only if node to be deleted is NOT the last node
							if (temp->next != NULL) {
								temp->next->prev = temp->prev;
							}
							else {
								tail = temp->prev;
							}

							// Change prev only if node to be deleted is NOT the first node
							if (temp->prev != NULL) {
								temp->prev->next = temp->next;
							}
							delete temp;
							numOfNodes--;
							return;
						}
					}
					else {
						if (p->next->numElements > p->next->getHalfNodeSize()) {
							p->removeAt(i);
							p->add(p->next->elements[0]);
							p->next->removeAt(0);
							return;
						}
						else {
							p->removeAt(i);
							for (int k = 0; k < p->next->getHalfNodeSize(); k++) {
								p->add(p->next->elements[k]);
							}
							// delete node p->next after Merger
							for (int k = p->next->getHalfNodeSize() - 1; k >= 0; k--) {
								p->next->removeAt(k);
							}
							Node* temp = p->next;
							/* Change next only if node to be deleted is NOT the last node */
							if (temp->next != NULL) {
								temp->next->prev = temp->prev;
							}
							else {
								tail = temp->prev;
							}

							/* Change prev only if node to be deleted is NOT the first node */
							if (temp->prev != NULL) {
								temp->prev->next = temp->next;
							}
							delete temp;
							numOfNodes--;
							return;
						}
					}
				}
			}
			count++;
		}
	}
	
}

int UnrolledLinkedList::firstIndexOf(int val) {
	int count = 0;
	if (head == NULL)
		return -1;
	for (Node*p = head; p != NULL; p = p->next)
	{
		for (int i = 0; i < p->numElements; i++)
		{
			if (p->elements[i] == val)
				return count;
			count++;
		}
	}
	return -1;
}

int UnrolledLinkedList::lastIndexOf(int val) {

	int count = size-1;
	for (Node*p = tail; p != NULL; p = p->prev) {
		for (int i = p->numElements - 1; i >= 0; i--) {
			if (p->elements[i] == val)
				return count;
			count--;
		}
	}
	return -1;
}

bool UnrolledLinkedList::contains(int val) {
	if (head == NULL)
		return false;
	for (Node*p = head; p != NULL; p = p->next)
	{
		for (int i = 0; i < p->numElements; i++)
		{
			if (p->elements[i] == val)
				return true;
		}
	}
	return false;
}

void UnrolledLinkedList::reverse() {
	// TODO
	//reserve element
	if (head == NULL) return;
	for (Node*p = head; p != NULL; p = p->next) {
		p->reverse();
	}
	//reserve node
	Node* temp = NULL;
	Node* current = head;
	/* swap next and prev for all nodes of
	doubly linked list */
	while (current != NULL) {
		temp = current->prev;
		current->prev = current->next;
		current->next = temp;
		current = current->prev;
	}
	tail = head;
	/* Before changing head, check for the cases like empty
	list and list with only one node */
	if (temp != NULL) 
		head = temp->prev;
}

int* UnrolledLinkedList::toArray() {
	// TODO
	if (head == NULL)
		return NULL;
	int* arr = new int[size];
	int count = 0;
	for (Node*p = head; p != NULL; p = p->next)
	{
		for (int i = 0; i < p->numElements; i++)
		{
			arr[count] = p->elements[i];
			count++;
		}
	}
	return arr;
}
