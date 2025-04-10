#pragma once

template<typename T>
class SinglyLinkedList
{
private:
	struct Node
	{
		T data;
		Node* next;
	};

public:
	class Iterator
	{
		friend class SinglyLinkedList;

	private:
		Node* prev;
		Node* curr;

	private:
		Iterator(Node* prev, Node* curr)
			: prev(prev), curr(curr)
		{

		}

	public:
		void operator++()
		{
			prev = curr;
			curr = curr->next;
		}

		T& operator*() const
		{
			return curr->data;
		}

	public:
		bool IsEnd() const
		{
			return curr == nullptr;
		}
	};

private:
	Node* head;
	Node* tail;

public:
	SinglyLinkedList()
		: head(nullptr), tail(nullptr)
	{

	}
	~SinglyLinkedList()
	{
		Clear();
	}

public:
	void Insert(const T& data)
	{
		Node* new_node = new Node{ data, nullptr };

		if (head == nullptr)
		{
			head = new_node;
			tail = new_node;
		}
		else
		{
			tail->next = new_node;
			tail = new_node;
		}
	}

	Iterator Remove(Iterator& iter)
	{
		if (iter.curr == nullptr)
		{
			return iter;
		}

		// 1.	delete_node(head)(tail)	- null
		// 2.	delete_node(head)		- node(tail)		- null
		// 3.	node(head)				- delete_node(tail)	- null
		// 4.	node(head)				- delete_node		- node(tail)	- null

		Iterator next(iter.prev, iter.curr->next);

		if (iter.curr->next != nullptr)
		{
			if (iter.prev != nullptr)
			{
				iter.prev->next = iter.curr->next; // 4
			}
			else
			{
				head = iter.curr->next; // 2
			}
		}
		else
		{
			if (iter.prev != nullptr)
			{
				iter.prev->next = nullptr; // 3
				tail = iter.prev;
			}
			else
			{
				head = tail = nullptr; // 1
			}
		}

		delete iter.curr;

		return next;
	}

	void Clear()
	{
		Node* current_node = head;
		Node* next_node = nullptr;
		while (current_node != nullptr)
		{
			next_node = current_node->next;

			delete current_node;

			current_node = next_node;
		}

		head = nullptr;
		tail = nullptr;
	}

	Iterator Begin() const
	{
		return Iterator(nullptr, head);
	}
};