#ifndef LIST
#define LIST
#include <iostream>
#include <memory>

template <typename T, typename Alloc = std::allocator<T>>
class list {
private:
	struct  BaseNode {
	private:
		BaseNode *m_next;
		BaseNode *m_prev;

	public:
		BaseNode(BaseNode *next, BaseNode *prev) : m_next(next), m_prev(prev) {}

	public:
		friend class list;
	};

private:
	struct Node : BaseNode {
	private:
		T m_value;

	public:
		Node(BaseNode *next, BaseNode *prev, const T &value) : BaseNode(next, prev), m_value(value) {}

	public:
		friend class list;
	};

private:
	struct Iterator {
	private:
		Node *m_node;

	public:
		using iterator_category = std::bidirectional_iterator_tag;

	public:
		Iterator() : m_node(nullptr) {};
		Iterator(Node *node) : m_node(node) {};
		Iterator(Node node) : m_node(&node) {};

	public:
		Iterator operator--() {
			m_node = static_cast<Node *>(m_node->m_prev);

			return *this;
		}

		Iterator operator++() {
			m_node = static_cast<Node *>(m_node->m_next);

			return *this;
		}

		bool operator==(const Iterator &other) const {
			return m_node == other.m_node;
		}

		bool operator!=(const Iterator &other) const {
			return m_node != other.m_node;
		}

	public:
		T &operator *() const {
			return m_node->m_value;
		}

		T &operator ->() const {
			return m_node->m_value;
		}
	};

private:
	BaseNode m_base_node;
	std::size_t m_size;

private:
	using RebindAlloc = typename std::allocator_traits<Alloc>::template rebind_alloc<Node>;
	using AllocTraits = std::allocator_traits<RebindAlloc>;
	RebindAlloc m_allocator;

public:
	list() : m_base_node(&m_base_node, &m_base_node), m_size(0) {}
	list(const RebindAlloc &allocator) : m_allocator(allocator), m_base_node(&m_base_node, &m_base_node), m_size(0) {}

	list(std::size_t count, const RebindAlloc &allocator = RebindAlloc()) :
		m_allocator(allocator), m_base_node(&m_base_node, &m_base_node), m_size(count) {

		Node *previous = nullptr;
		for (std::size_t i = 0; i < count; ++i) {

			Node *current = nullptr;

			try {
				if (i == 0) {
					current = AllocTraits::allocate(m_allocator, 1);
					AllocTraits::construct(m_allocator, current, &m_base_node, nullptr, T());

					previous = current;
					m_base_node.m_next = current;
					m_base_node.m_prev = current;
				} else if (i == count - 1 && i != 0) {
					current = AllocTraits::allocate(m_allocator, 1);
					previous->m_next = current;
					AllocTraits::construct(m_allocator, current, &m_base_node, previous, T());

					previous = current;
					m_base_node.m_prev = current;
				} else {
					current = AllocTraits::allocate(m_allocator, 1);
					previous->m_next = current;
					AllocTraits::construct(m_allocator, current, nullptr, previous, T());

					previous = current;
				}
			} catch (...) {

				while (current) {
					AllocTraits::destroy(m_allocator, current);
					AllocTraits::deallocate(m_allocator, current, 1);

					current = previous;
					if (previous)
						previous = static_cast<Node *>(previous->m_prev);
				}

				m_size = 0;
				m_base_node.m_next = &m_base_node;
				m_base_node.m_prev = &m_base_node;

				return;
			}
		}
	}

	list(std::size_t count, const T &value, const RebindAlloc &allocator = RebindAlloc())
		: m_allocator(allocator), m_base_node(&m_base_node, &m_base_node), m_size(count) {

		Node *previous = nullptr;
		for (std::size_t i = 0; i < count; ++i) {
			Node *current = nullptr;

			try {
				if (i == 0) {
					current = AllocTraits::allocate(m_allocator, 1);
					AllocTraits::construct(m_allocator, current, &m_base_node, nullptr, value);

					previous = current;
					m_base_node.m_next = current;
					m_base_node.m_prev = current;
				}
				else if (i == count - 1 && i != 0) {
					current = AllocTraits::allocate(m_allocator, 1);
					previous->m_next = current;
					AllocTraits::construct(m_allocator, current, &m_base_node, previous, value);

					previous = current;
					m_base_node.m_prev = current;
				} else {
					current = AllocTraits::allocate(m_allocator, 1);
					previous->m_next = current;
					AllocTraits::construct(m_allocator, current, nullptr, previous, value);

					previous = current;
				}
			} catch (...) {

				while (current) {
					AllocTraits::destroy(m_allocator, current);
					AllocTraits::deallocate(m_allocator, current, 1);

					current = previous;
					if (previous)
						previous = static_cast<Node *>(previous->m_prev);
				}

				m_size = 0;
				m_base_node.m_next = &m_base_node;
				m_base_node.m_prev = &m_base_node;

				return;
			}
		}
	}

public:
	~list() {
		while (!empty())
			pop_front();
	}

public:
	T &back() const{
		return static_cast<Node *>(m_base_node.m_prev)->m_value;
	}

	T &front() const{
		return static_cast<Node *>(m_base_node.m_next)->m_value;
	}

public:
	void push_front(const T &value) {
		Node *new_node = AllocTraits::allocate(m_allocator, 1);

		try {
			if (m_size != 0)
				AllocTraits::construct(m_allocator, new_node, m_base_node.m_next, nullptr, value);
			else {
				AllocTraits::construct(m_allocator, new_node, &m_base_node, nullptr, value);
				m_base_node.m_prev = new_node;
			}
		}
		catch (...) {
			AllocTraits::destroy(m_allocator, new_node);
			AllocTraits::deallocate(m_allocator, new_node, 1);

			return;
		}

		(m_base_node.m_next)->m_prev = new_node;
		m_base_node.m_next = new_node;

		++m_size;
	}

	void push_back(const T &value) {
		Node *new_node = AllocTraits::allocate(m_allocator, 1);
		try {
			if (m_size != 0)
				AllocTraits::construct(m_allocator, new_node, &m_base_node, m_base_node.m_prev, value);
			else {
				AllocTraits::construct(m_allocator, new_node, &m_base_node, nullptr, value);
				m_base_node.m_next = new_node;
			}
		} 
		catch (...) {
			AllocTraits::destroy(m_allocator, new_node);
			AllocTraits::deallocate(m_allocator, new_node, 1);

			return;
		}

		(m_base_node.m_prev)->m_next = new_node;
		m_base_node.m_prev = new_node;

		++m_size;
	}

public:
	void pop_front() {
		if (empty())
			return;

		Node *first = static_cast<Node *>(m_base_node.m_next);

		if (m_size == 1) {
			m_base_node.m_next = &m_base_node;
			m_base_node.m_prev = &m_base_node;
		}
		else {
			m_base_node.m_next = first->m_next;
			(first->m_next)->m_prev = nullptr;
		}

		--m_size;

		AllocTraits::destroy(m_allocator, first);
		AllocTraits::deallocate(m_allocator, first, 1);
	}

	void pop_back() {
		if (empty())
			return;

		Node *last = static_cast<Node *>(m_base_node.m_prev);

		if (m_size == 1) {
			m_base_node.m_next = &m_base_node;
			m_base_node.m_prev = &m_base_node;
		}
		else {
			m_base_node.m_prev = last->m_prev;
			(last->m_prev)->m_next = &m_base_node;
		}

		--m_size;

		AllocTraits::destroy(m_allocator, last);
		AllocTraits::deallocate(m_allocator, last, 1);
	}

public: 
	bool empty() const { return m_size == 0; }
	std::size_t size() const { return m_size; }

public:
	Iterator end() {
		return Iterator(static_cast<Node *>(&m_base_node));
	}

	Iterator begin() {
		return Iterator(static_cast<Node *>(m_base_node.m_next));
	}
};
#endif
