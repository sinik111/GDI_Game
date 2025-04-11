#pragma once

#include <memory>
#include <string>

template <typename T>
class HashMap
{
private:
	struct Node
	{
		std::string key;
		T value;
		Node* next;
	};

public:
	class Iterator
	{
		friend class HashMap;

	private:
		int index;
		const int max_table;
		Node** hash_table;
		Node* curr;

	private:
		Iterator(int index, int max_table, Node** hash_table)
			: index(index), max_table(max_table), hash_table(hash_table), curr(nullptr)
		{
			while (this->index < this->max_table)
			{
				if (this->hash_table[this->index] != nullptr)
				{
					this->curr = this->hash_table[this->index];

					break;
				}

				++(this->index);
			}
		}

	public:
		void operator++()
		{
			if (this->curr == nullptr)
			{
				return;
			}

			if (this->curr->next != nullptr)
			{
				this->curr = this->curr->next;
			}
			else
			{
				++(this->index);

				while (this->index < this->max_table)
				{
					if (this->hash_table[this->index] != nullptr)
					{
						this->curr = this->hash_table[this->index];

						return;
					}

					++(this->index);
				}

				this->curr = nullptr;
			}
		}

		T& operator*() const
		{
			return this->curr->value;
		}

	public:
		bool IsEnd() const
		{
			return index == this->max_table;
		}
	};

private:
	const int max_table = 100;
	Node* hash_table[100];

public:
	HashMap()
	{
		for (int i = 0; i < max_table; ++i)
		{
			hash_table[i] = nullptr;
		}
	}
	HashMap(const HashMap&) = delete;
	~HashMap()
	{
		Clear();
	}

public:
	void Insert(const std::string& key, const T& value)
	{
		int hash = Hash(key);

		if (hash_table[hash] == nullptr)
		{
			Node* new_node = new Node{ key, value, nullptr };

			hash_table[hash] = new_node;
		}
		else
		{
			bool has = false;

			Node* current_node = hash_table[hash];
			while (current_node->next != nullptr)
			{
				if (current_node->key == key)
				{
					has = true;

					break;
				}

				current_node = current_node->next;
			}

			if (current_node->key == key)
			{
				has = true;
			}

			if (has)
			{
				current_node->value = value;
			}
			else
			{
				Node* new_node = new Node{ key, value, nullptr };

				current_node->next = new_node;
			}
		}
	}

	bool Find(const std::string& key, T& out)
	{
		int hash = Hash(key);

		Node* current_node = hash_table[hash];
		while (current_node != nullptr)
		{
			if (current_node->key == key)
			{
				out = current_node->value;

				return true;
			}

			current_node = current_node->next;
		}

		return false;
	}

	void Delete(const std::string& key)
	{
		int hash = Hash(key);

		if (hash_table[hash] == nullptr)
		{
			return;
		}
		else
		{
			Node* previous_node = nullptr;
			Node* current_node = hash_table[hash];
			while (current_node != nullptr)
			{
				if (current_node->key == key)
				{
					if (previous_node != nullptr)
					{
						previous_node->next = current_node->next;
					}
					else
					{
						hash_table[hash] = current_node->next;
					}

					delete current_node;

					current_node = nullptr;

					break;
				}

				previous_node = current_node;
				current_node = current_node->next;
			}
		}
	}

	void Clear()
	{
		for (int i = 0; i < max_table; ++i)
		{
			Node* next = nullptr;
			Node* current = hash_table[i];
			while (current != nullptr)
			{
				next = current->next;

				delete current;

				current = nullptr;

				current = next;
			}

			hash_table[i] = nullptr;
		}
	}

	Iterator Begin()
	{
		return Iterator(0, max_table, hash_table);
	}

private:
	int Hash(const std::string& str)
	{
		unsigned long hash = 5381;
		int c;

		auto iter = str.begin();
		while (iter != str.end())
		{
			c = *iter++;
			hash = ((hash << 5) + hash) + c;
		}

		return (int)(hash % max_table);
	}
};