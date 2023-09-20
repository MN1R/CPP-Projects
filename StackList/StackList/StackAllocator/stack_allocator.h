#ifndef STACK_ALLOCATOR
#define STACK_ALLOCATOR
#include <cstddef>

static constexpr std::size_t STACK_SIZE = 10000;

template <typename T>
class stack_allocator {
private:
	alignas(std::max_align_t) static unsigned char m_memory[STACK_SIZE];
	static unsigned char *m_top;
	
public:
	stack_allocator() {}

	template<class U>
	stack_allocator(const stack_allocator<U> &other) {}

public:
	~stack_allocator() {}

public:
	static T *allocate(std::size_t count) {
		T *storage = reinterpret_cast<T *>(m_top);
		m_top += (count * sizeof(T));

		return storage;
	}

	static void deallocate(T *ptr, std::size_t count) {}

public:
	T *allocate_node() {
		return allocate(1);
	}

	void deallocate_node(T *node) {
		deallocate(node, 1);
	}

public:
	using value_type = T;

public:
	template <typename U>
	struct rebind {
		using other = stack_allocator<U>;
	};
};

template <typename T>
unsigned char stack_allocator<T>::m_memory[STACK_SIZE];

template <typename T>
unsigned char *stack_allocator<T>::m_top = stack_allocator<T>::m_memory;
#endif